#ifndef _THRIFT_CLIENT_MULTI_CONNECT_PLUG_H_
#define _THRIFT_CLIENT_MULTI_CONNECT_PLUG_H_

// 解除注释即可打印信息
//#define PRINT_INFO

// 机器下线、上线信息较为关键
#define PRINT_ADD_DELETE_INFO

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>

#include <atomic>
#include <boost/algorithm/string.hpp>
#include <condition_variable>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include "nlohmann/json.hpp"
#include "parameter_server/util/RWLock.h"
#include "zkclient.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using std::condition_variable;
using std::map;
using std::move;
using std::mutex;
using std::pair;
using std::set;
using std::shared_ptr;
using std::string;
using std::thread;
using std::to_string;
using std::unique_lock;
using std::vector;
using json = nlohmann::json;

// 每BALCKLIST_TIME秒刷新一次黑名单
#define BALCKLIST_TIME double(5)

typedef string STR_ip_port;
typedef string STR_ip_port_suffix;
typedef ::apache::thrift::stdcxx::shared_ptr<TTransport>
    atsstt;  // 取每个namespace的第一个字母胡乱命名

enum CThriftClinetMultiConnectPlugErrorCode {
  EC_SUCCESS = 0,  // 操作成功
  ERR_INIT_INIT,
};

// 连接池状态机
enum CONNECT_STATUS {
  CONNECT_OK = 0,   // 正常
  CONNECT_USING,    // 使用中
  CONNECT_OFFLINE,  // 下线
};
// 连接池结点
template <class T>
struct connectNode {
  T client;                           // 服务客户端
  STR_ip_port_suffix connectNodeKey;  // 形如127.0.0.1:1234_x
  atsstt transport;                   // for close
  shared_ptr<mutex> connectMutex;
  shared_ptr<condition_variable> connectCondition;
  shared_ptr<int> status;  // 0空闲，1使用中，2销毁
  connectNode(T c)
      : client(c),
        connectMutex(new mutex),
        connectCondition(new condition_variable),
        status(new int(0)) {}
};

// 连接池状态机
enum CONNECT_POOL_NODE_STATUS {
  POOL_OK = 0,   // 正常
  POOL_OFFLINE,  // 下线
};
// 连接池数据结构
template <class T>
struct connectPoolNode {
  shared_ptr<RWLock>
      sptr_rwmtx_connectPool;  // 互斥量,
                               // mutex拷贝、=运算符都是delete，放在标准容器中必须这么用
  int status;        // 连接池状态， 详见 CONNECT_POOL_NODE_STATUS
  int connect_step;  // 计数器
  map<STR_ip_port_suffix, connectNode<T>> pool;  //连接池
  connectPoolNode() : status(0), connect_step(0) {}

  connectPoolNode(map<STR_ip_port_suffix, connectNode<T>>&& p)
      : sptr_rwmtx_connectPool(new RWLock),
        status(0),
        connect_step(0),
        pool(p) {}
};

// thrift客户端多链接插件类
template <class T>
class CThriftClinetMultiConnectPlug {
 public:
  /*
   * 构造函数
   * @zkHost:zookeeper集群url
   * @zkPath:服务信息存放路径
   * @connectNumber:每个服务创建的最大连接数, 推荐大于调用线程总数
   * @timeout:zk和具体thrift server的超时时间
   * @checkTimes:后台线程每秒检查连接池的次数
   */
  CThriftClinetMultiConnectPlug(const string zkHost, const string zkPath,
                                const int connectNumber,
                                const int timeout = 1000 * 10,
                                const double checkTimes = 1.0)
      : m_zkHost(zkHost),
        m_zkPath(zkPath),
        m_connectNumber(connectNumber),
        m_timeout(timeout),
        m_checkTimes(checkTimes),
        m_ptrThread(nullptr),
        m_threadRun(true),
        m_connectSuffix(0) {}

  /*
   * 初始化zk链接
   * 获取ip/port、创建连接池
   * 创建线程监控zk
   * 返回0代表成功，其他失败
   */
  int init();

  /*
   * 析构函数
   */
  virtual ~CThriftClinetMultiConnectPlug();

 protected:
  /*
   * 【主线程接口】【纯虚函数】创建链接节点并挂在连接池上
   */
  virtual void createConnect(map<STR_ip_port_suffix, connectNode<T>>& pool,
                             const string& ip, const int port) = 0;

  /*
   * 【主线程接口】为thrift客户端返回一个连接
   */
  connectNode<T>* getThriftConnect();

  /*
   * 【主线程接口】删除指定链接
   */
  bool deleteClient(STR_ip_port_suffix connectNodeKey);

 private:
  /*
   * 【后台线程接口】向各个连接池中加客户端
   */
  void addClient2ConnectPool();

  /*
   * 【后台线程接口】服务上线
   */
  void addServerInfo(vector<string>* input_ip_port_weight = nullptr);

  /*
   * 【后台线程接口】服务下线
   */
  void deleteServerInfo(vector<string>& childNode);

 protected:
  /*
   * 获取connectNodeKey
   */
  string getConnectPoolKey(const string& connectNodeKey);

 private:
  /*
   * 创建连接池
   */
  void createConnectPool();

  /*
   * 更新连接池
   */
  void updateConnectPool();

  /*
   * 主动监控zk信息变化
   */
  void watchZK();

  /*
   * 判断待连接ip是否在黑名单中
   */
  bool inBlacklist(const string& ip, const int port);

  /*
   * 将黑名单中存在了抄过BALCKLIST_TIME时长的信息删除
   */
  void updateBlacklist();

  /*
   * NAME: watchGetChildren:,子节点watch方法，监控zk变化
   * errcode
   * path
   * count :子节点个数
   * data :子节点名称字符串数组（* 遍历时需要用count控制，否则必炸）
   * context :调用时传入的数据(此处为this指针)
   */
  static void watchGetChildren(ZKErrorCode errcode, const std::string& path,
                               int count, char** data, void* context);

  /*
   * 获取zk信息
   */
  void getZKInfo(vector<string>& vec_zk_info, bool watch = false);

 protected:
  const string m_zkHost;      // zk服务地址
  const string m_zkPath;      // zk父节点路径
  const int m_connectNumber;  // 每个ip:port创建的链接个数
  const int m_timeout;        // thrift服务超时时间
  const double m_checkTimes;  // 每秒主动拉取zk新数据的次数
  ZKClient m_zkClinet;        // zk连接句柄
  thread* m_ptrThread;        // 旁路线程，监听zk信息
  bool m_threadRun;  // 旁路线程是否运行参数，析构时会置为false
  int m_connectSuffix;  // 不同连接做后缀，用来区分

 protected:
  RWLock m_rwmtx_serverInfo;                           // 服务信息读写锁
  set<STR_ip_port> m_serverInfo;                       // 记录线上服务
  map<STR_ip_port, connectPoolNode<T>> m_connectPool;  // 链接池

  RWLock m_rwmtx_blacklist;
  map<STR_ip_port, time_t>
      m_blacklist;  // 黑名单，BALCKLIST_TIME 秒之内不尝试重连
};

/*
**********************************************************************
********* 派生类调用的模板方法不支持分离编译，必须在声明的文件里实例化 *********
**********************************************************************
*/

template <class T>
CThriftClinetMultiConnectPlug<T>::~CThriftClinetMultiConnectPlug() {
  // 关闭线程
  if (m_ptrThread) {
    m_threadRun = false;
    m_ptrThread->join();
    delete m_ptrThread;
  }

  // 关闭所有链接
  for (auto it : m_connectPool) {
    for (auto itt : it.second.pool) {
      itt.second.transport->close();
    }
  }
}

template <class T>
connectNode<T>* CThriftClinetMultiConnectPlug<T>::getThriftConnect() {
  static int step = 0;
  connectNode<T>* p2connect = nullptr;

  m_rwmtx_serverInfo.lockRead();
  int serverNumber = static_cast<int>(m_connectPool.size());
  if (serverNumber == 0) {
    m_rwmtx_serverInfo.unlockRead();
    p2connect = nullptr;
  } else {
    int pool_step = step % serverNumber;
    auto it = m_connectPool.begin();
    while (pool_step--) ++it;
    step = step > 12345 ? 0 : step + 1;

    // ReadGuard Zone
    {
      ReadGuard rr(*(it->second.sptr_rwmtx_connectPool));
      m_rwmtx_serverInfo.unlockRead();
      int connectPoolSize = static_cast<int>(it->second.pool.size());
      // 连接池不是正常状态或者为空直接返回空(尽管其他连接池有可用)
      if (it->second.status != POOL_OK || connectPoolSize == 0) {
        p2connect = nullptr;
      } else {
        int connect_step = it->second.connect_step % connectPoolSize;
        auto itt = it->second.pool.begin();
        while (connect_step--) ++itt;
        p2connect = &(itt->second);
        it->second.connect_step =
            it->second.connect_step > 12345 ? 0 : it->second.connect_step + 1;
#ifdef PRINT_INFO
        printf("   get [%s]", (itt->first).c_str());
#endif
      }
    }
  }

  return p2connect;
}

template <class T>
bool CThriftClinetMultiConnectPlug<T>::deleteClient(
    STR_ip_port_suffix connectNodeKey) {
  if (connectNodeKey.empty()) {
    return false;
  }

  // 需要考虑多线程并发删除的问题（主线程调用deleteClient、同时后台线程调用deleteServerInfo）
  bool ret = false;

  vector<string> ip_port_suffix;
  boost::split(ip_port_suffix, connectNodeKey, boost::is_any_of("_"),
               boost::token_compress_on);

  m_rwmtx_serverInfo.lockRead();

  // 队列存在并且状态不是已经下线
  if (m_connectPool.find(ip_port_suffix[0]) != m_connectPool.end() &&
      m_connectPool[ip_port_suffix[0]].status != POOL_OFFLINE) {
    WriteGuard l(*(m_connectPool[ip_port_suffix[0]].sptr_rwmtx_connectPool));
    m_rwmtx_serverInfo.unlockRead();

    // 连接节点存在并且不是下线状态
    if (m_connectPool[ip_port_suffix[0]].pool.find(connectNodeKey) !=
            m_connectPool[ip_port_suffix[0]].pool.end() &&
        *(m_connectPool[ip_port_suffix[0]]
              .pool.find(connectNodeKey)
              ->second.status) != CONNECT_OFFLINE
        // 这种写法报错，不知道原因。。
        // m_connectPool[ip_port_suffix[0]].pool[connectNodeKey];
    ) {
      m_connectPool[ip_port_suffix[0]]
          .pool.find(connectNodeKey)
          ->second.transport->close();
      m_connectPool[ip_port_suffix[0]].pool.erase(connectNodeKey);
      ret = true;
#ifdef PRINT_ADD_DELETE_INFO
      printf("   [deleteClient] in main thread [%s] ...\n",
             connectNodeKey.c_str());
#endif
    } else {
      ret = false;
    }
  } else {
    ret = false;
    m_rwmtx_serverInfo.unlockRead();
  }

  return ret;
}

// 获取zk信息
template <class T>
void CThriftClinetMultiConnectPlug<T>::getZKInfo(vector<string>& vec_zk_info,
                                                 bool watch) {
  vector<string> vecChildNode;
  m_zkClinet.GetChildren(m_zkPath, &vecChildNode,
                         watch ? watchGetChildren : nullptr,
                         watch ? static_cast<void*>(this) : nullptr, watch);

  for (auto it : vecChildNode) {
    char szBuf[4096 * 10] = {0};  // 获取信息, 形如: 127.0.0.1:9090:10
    int iLength = (int)sizeof(szBuf);
    m_zkClinet.GetNode(m_zkPath + "/" + it, szBuf, &iLength);
    vec_zk_info.emplace_back(szBuf);
  }
}

template <class T>
void CThriftClinetMultiConnectPlug<T>::addServerInfo(
    vector<string>* input_ip_port_weight)

{
  vector<string>* p2zkInfo = nullptr;
  vector<string>
      vec_zk_info;  // 初始化时有用，回调时无用，用以减少回调时的数据拷贝，提高性能

  // init时，需要注册子节点的watch
  if (input_ip_port_weight == nullptr) {
    p2zkInfo = &vec_zk_info;

    getZKInfo(vec_zk_info, true);
  }
  // watch回调时，直接取值即可
  else {
    p2zkInfo = input_ip_port_weight;
  }

  if (p2zkInfo->empty()) return;

  for (auto it : *p2zkInfo) {
    json jZkInfo;
    try {
      jZkInfo = json::parse(it);
    } catch (...) {
      std::cout << "Error msg: parse layers failed in addServerInfo function!"
                << std::endl;
      continue;
    }
    const string ip = jZkInfo["ip"];
    const int port = jZkInfo["port"];
    const string ip_port = ip + ":" + to_string(port);
    if (m_serverInfo.find(ip_port) == m_serverInfo.end() &&
        !inBlacklist(ip, port)) {
      // 创建连接池的的单个结点
      map<STR_ip_port_suffix, connectNode<T>> connectPool;
      try {
        int number = m_connectNumber;  //尝试创建client个数
        while (number--) {
          createConnect(connectPool, ip, port);
        }
      } catch (apache::thrift::transport::TTransportException& e) {
        // 链接失败的加入黑名单， BALCKLIST_TIME秒内不再重连
        time_t now;
        time(&now);
        {
          WriteGuard w(m_rwmtx_blacklist);
          m_blacklist[ip_port] = now;
        }
      } catch (...) {
        // 链接失败的加入黑名单， BALCKLIST_TIME秒内不再重连
        time_t now;
        time(&now);
        {
          WriteGuard w(m_rwmtx_blacklist);
          m_blacklist[ip_port] = now;
        }
      }

      // 若创建的连接池结点存在可用链接，则挂在连接池上
      if (connectPool.size() > 0) {
        WriteGuard w(m_rwmtx_serverInfo);
        m_serverInfo.insert(ip_port);
        m_connectPool.insert(pair<STR_ip_port, connectPoolNode<T>>(
            ip_port, connectPoolNode<T>(move(connectPool))));
#ifdef PRINT_ADD_DELETE_INFO
        for (auto it : m_connectPool[ip_port].pool)
          printf("[addServerInfo]:  %s\n", it.first.data());
#endif
      }
    }
  }
}

template <class T>
void CThriftClinetMultiConnectPlug<T>::createConnectPool() {
  addServerInfo();
}

template <class T>
void CThriftClinetMultiConnectPlug<T>::deleteServerInfo(
    vector<string>& ip_port_weight) {
  /*
   * 暂时不感知zk权重信息变化。
   */
  set<STR_ip_port> SET_ip_port;
  for (auto it : ip_port_weight) {
    json jZkInfo;
    try {
      jZkInfo = json::parse(it);
    } catch (...) {
      std::cout
          << "Error msg: parse layers failed in deleteServerInfo function!"
          << std::endl;
      continue;
    }
    const string ip = jZkInfo["ip"];
    const int port = jZkInfo["port"];
    const string ip_port = ip + ":" + to_string(port);
    SET_ip_port.emplace(move(ip_port));
  }

  for (auto it : m_serverInfo) {
    if (SET_ip_port.find(it) == SET_ip_port.end() &&
        m_connectPool[it].status != POOL_OFFLINE) {
      // 只有这里会更改status信息，不存在竞态条件，不需要加锁
      m_connectPool[it].status = POOL_OFFLINE;
    }
  }

  for (auto it = m_connectPool.begin(); it != m_connectPool.end();) {
    if (it->second.status == POOL_OFFLINE) {
      map<STR_ip_port_suffix, connectNode<T>> pool;

      // 先解链
      {
        WriteGuard w(m_rwmtx_serverInfo);
        {
          // 跟其他资源竞争一下这个连接池的锁，这里正常通过则不会再有地方使用这把锁，可以放心销毁
          WriteGuard ww(*(it->second.sptr_rwmtx_connectPool));
        }
        m_serverInfo.erase(m_serverInfo.find(it->first));
        pool = move(it->second.pool);
        m_connectPool.erase(it++);
      }

      // 再逐个删除
      {
        for (auto itt = pool.begin(); itt != pool.end();) {
          // 需要考虑多线程并发删除的问题
          shared_ptr<mutex> mtx = itt->second.connectMutex;
          shared_ptr<condition_variable> cond = itt->second.connectCondition;
          shared_ptr<int> status = itt->second.status;
          {
            unique_lock<mutex> u(*mtx);
            cond->wait(u, [status]() { return *status != CONNECT_USING; });
            if (*status == CONNECT_OK) {
#ifdef PRINT_ADD_DELETE_INFO
              printf("   [deleteServerInfo] %s\n", itt->first.data());
#endif
              itt->second.transport->close();
              pool.erase(itt++);
              *status = CONNECT_OFFLINE;
              cond->notify_all();
            } else {
              // 该节点已经被主线程已经删除完毕，迭代器已经失效，从头开始赋值
              itt = pool.begin();
            }
          }
        }
      }
    } else {
      ++it;
    }
  }
}

template <class T>
void CThriftClinetMultiConnectPlug<T>::updateConnectPool() {
  m_ptrThread = new thread(&CThriftClinetMultiConnectPlug::watchZK, this);
}

template <class T>
void CThriftClinetMultiConnectPlug<T>::watchZK() {
  // 每(1000 * 1000 / m_checkTimes)秒主动跑1次，兜底更新数据
  while (m_threadRun) {
    // 向各个连接池中加客户端
    addClient2ConnectPool();

    vector<string> vec_zk_info;
    getZKInfo(vec_zk_info);

    addServerInfo(&vec_zk_info);

    deleteServerInfo(vec_zk_info);

    updateBlacklist();

    if (m_threadRun) usleep(static_cast<int>(1000 * 1000 / m_checkTimes));
  }
}

template <class T>
bool CThriftClinetMultiConnectPlug<T>::inBlacklist(const string& ip,
                                                   const int port) {
  bool ret = true;

  time_t now;
  time(&now);
  string&& ip_port = ip + ":" + to_string(port);

  {
    ReadGuard r(m_rwmtx_blacklist);
    // 在黑名单
    if (m_blacklist.find(ip_port) != m_blacklist.end()) {
      // 在黑名单内且为BALCKLIST_TIME秒以内， 则认为在黑名单
      if (difftime(now, m_blacklist[ip_port]) < BALCKLIST_TIME) {
        ret = true;
      }
      // 在黑名单但是是BALCKLIST_TIME秒以外，则认为不在黑名单
      else {
        ret = false;
      }
    }
    // 不在黑名单
    else {
      ret = false;
    }
  }

  return ret;
}

template <class T>
void CThriftClinetMultiConnectPlug<T>::updateBlacklist() {
  time_t now;
  time(&now);

  {
    WriteGuard w(m_rwmtx_blacklist);
    for (auto it = m_blacklist.begin(); it != m_blacklist.end();) {
      if (difftime(now, it->second) > BALCKLIST_TIME) {
        m_blacklist.erase(it++);
      } else
        ++it;
    }
  }
}

/*
 * NAME: watchGetChildren:,子节点watch方法，监控zk变化
 * errcode
 * path
 * count :子节点个数
 * data :子节点名称字符串数组（* 遍历时需要用count控制，否则必炸）
 * context :调用时传入的数据(此处为this指针)
 */
template <class T>
void CThriftClinetMultiConnectPlug<T>::watchGetChildren(ZKErrorCode errcode,
                                                        const std::string& path,
                                                        int count, char** data,
                                                        void* context) {
  CThriftClinetMultiConnectPlug* p2this =
      static_cast<CThriftClinetMultiConnectPlug*>(context);

  vector<string> vec_zk_info;
  p2this->getZKInfo(vec_zk_info);

  if (errcode == kZKSucceed) {
    p2this->addServerInfo(&vec_zk_info);

    p2this->deleteServerInfo(vec_zk_info);
  }
}

template <class T>
int CThriftClinetMultiConnectPlug<T>::init() {
  // 初始化zk连接
  {
    if (!m_zkClinet.Init(m_zkHost.c_str(), 1000 * 60)) return ERR_INIT_INIT;
  }

  // 创建链接池
  createConnectPool();

  // 创建旁路线程，监控并更新链接池
  updateConnectPool();

  return EC_SUCCESS;
}

template <class T>
void CThriftClinetMultiConnectPlug<T>::addClient2ConnectPool() {
  //为了不过分影响并发速度，每次最多只维护一个队列或者不加
  ReadGuard r(m_rwmtx_serverInfo);
  for (auto& it : m_connectPool) {
    if (it.second.pool.size() < m_connectNumber &&
        it.second.status != POOL_OFFLINE) {
      WriteGuard r(*(it.second.sptr_rwmtx_connectPool));
      int number =
          m_connectNumber - it.second.pool.size();  //尝试创建client个数
      vector<string> ip_port;
      boost::split(ip_port, it.first, boost::is_any_of(":"),
                   boost::token_compress_on);
      if (!inBlacklist(ip_port[0], stoi(ip_port[1]))) {
        try {
          while (number--) {
            createConnect(it.second.pool, ip_port[0], stoi(ip_port[1]));
#ifdef PRINT_ADD_DELETE_INFO
            printf("   [addClient2ConnectPool] %s_%d\n", it.first.data(),
                   m_connectSuffix);
#endif
          }
        } catch (apache::thrift::transport::TTransportException& e) {
          // 链接失败的加入黑名单， BALCKLIST_TIME秒内不再重连
          time_t now;
          time(&now);
          {
            WriteGuard w(m_rwmtx_blacklist);
            m_blacklist[it.first] = now;
          }
        } catch (...) {
          // 链接失败的加入黑名单， BALCKLIST_TIME秒内不再重连
          time_t now;
          time(&now);
          {
            WriteGuard w(m_rwmtx_blacklist);
            m_blacklist[it.first] = now;
          }
        }
      }
    }
  }
}

template <class T>
string CThriftClinetMultiConnectPlug<T>::getConnectPoolKey(
    const string& ip_port) {
  int this_connectSuffix = m_connectSuffix;
  ++m_connectSuffix;
  return move(ip_port + "_" + to_string(this_connectSuffix));
}

// 调用客户端方法时返回值
enum RETURN_CODE_USE_tcmcp {
  USE_tcmcp_SUCCESS = 0,      // 操作成功
  USE_tcmcp_NO_CONNECT,       // 无服务在线
  USE_tcmcp_CONNECT_ERROR,    // 连接异常
  USE_tcmcp_UNKNOWN,          // 未知错误
  USE_tcmcp_CONNECT_OFFLINE,  // 服务端下线
  USE_tcmcp_INPUT_ERROR       // 输入参数异常
};

/*
 * 客户端方法返回值为【POD】类型时的宏
 *
 * USE_tcmcp_POD(类名, thrift客户端方法名, 返回值, (输入列表))
 *   ——输入列表需要与真正调用的thrift方法顺序严格一致, 且必须用()括起来!!!
 */
#define USE_tcmcp_POD(__CLIENT_TYPE__, __CLIENT_FUN__, __RETURN__, __ARGS__) \
  int rc = -1;                                                               \
  connectNode<__CLIENT_TYPE__>* p2connect = getThriftConnect();              \
  if (p2connect == nullptr) {                                                \
    rc = USE_tcmcp_NO_CONNECT;                                               \
  } else {                                                                   \
    try {                                                                    \
      __RETURN__ = p2connect->client.__CLIENT_FUN__ __ARGS__;                \
      rc = USE_tcmcp_SUCCESS;                                                \
    } catch (apache::thrift::transport::TTransportException & e) {           \
      std::cout << "Warning msg: " << e.what() << std::endl;                 \
      deleteClient(p2connect->connectNodeKey);                               \
      rc = USE_tcmcp_CONNECT_ERROR;                                          \
    } catch (std::exception & e) {                                           \
      rc = USE_tcmcp_UNKNOWN;                                                \
    }                                                                        \
  }                                                                          \
  return rc

/*
 * 客户端方法返回值为【非POD】类型时的宏
 *
 * USE_tcmcp_NOT_POD(类名, thrift客户端方法名, (输入列表))
 *   ——输入列表需要与真正调用的thrift方法顺序严格一致, 且必须用()括起来!!!
 */
#define USE_tcmcp_NOT_POD(__CLIENT_TYPE__, __CLIENT_FUN__, __ARGS__)   \
  int rc = -1;                                                         \
  connectNode<__CLIENT_TYPE__>* p2connect = getThriftConnect();        \
  if (p2connect == nullptr) {                                          \
    rc = USE_tcmcp_NO_CONNECT;                                         \
  } else {                                                             \
    shared_ptr<mutex> mtx = p2connect->connectMutex;                   \
    shared_ptr<condition_variable> cond = p2connect->connectCondition; \
    shared_ptr<int> status = p2connect->status;                        \
    {                                                                  \
      unique_lock<mutex> u(*mtx);                                      \
      cond->wait(u, [status]() { return *status != CONNECT_USING; });  \
      try {                                                            \
        if (*status == CONNECT_OK) {                                   \
          *status = CONNECT_USING;                                     \
          p2connect->client.__CLIENT_FUN__ __ARGS__;                   \
          *status = CONNECT_OK;                                        \
          cond->notify_one();                                          \
          rc = USE_tcmcp_SUCCESS;                                      \
        } else {                                                       \
          cond->notify_one();                                          \
          rc = USE_tcmcp_CONNECT_OFFLINE;                              \
        }                                                              \
      } catch (apache::thrift::transport::TTransportException & e) {   \
        std::cout << "Warning msg: " << e.what() << std::endl;         \
        if (deleteClient(p2connect->connectNodeKey)) {                 \
          *status = CONNECT_OFFLINE;                                   \
        }                                                              \
        cond->notify_one();                                            \
        \     
                if (!strncmp(e.what(), "No more data to read.",        \
                             strlen("No more data to read.")))\ 
                    rc = USE_tcmcp_CONNECT_OFFLINE;                    \
        \       
                else rc = USE_tcmcp_CONNECT_ERROR;                     \
      } catch (std::exception & e) {                                   \
        *status = CONNECT_OK;                                          \
        cond->notify_one();                                            \
        if (strstr(e.what(), "failed: unknown result"))                \
          rc = USE_tcmcp_INPUT_ERROR;                                  \
        else                                                           \
          rc = USE_tcmcp_UNKNOWN;                                      \
        std::cout << e.what() << std::endl;                            \
      }                                                                \
    }                                                                  \
  }                                                                    \
  return rc

// 默认创建TFramedTransport、TBinaryProtocol类型客户端
#define CREATE_CONNECT_TFramedTransport_TBinaryProtocol(__CLIENT_TYPE__) \
  string ip_port = ip + ":" + to_string(port);                           \
  shared_ptr<TSocket> socket(new TSocket(ip, port));                     \
  socket->setRecvTimeout(m_timeout);                                     \
  shared_ptr<TTransport> transport(new TFramedTransport(socket));        \
  shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));        \
  transport->open();                                                     \
  connectNode<__CLIENT_TYPE__> connect(move(__CLIENT_TYPE__(protocol))); \
  connect.connectNodeKey = getConnectPoolKey(ip_port);                   \
  connect.transport = transport;                                         \
  pool.insert(pair<STR_ip_port_suffix, connectNode<__CLIENT_TYPE__>>(    \
      connect.connectNodeKey, move(connect)))

#endif  //_THRIFT_CLIENT_MULTI_CONNECT_PLUG_H_
