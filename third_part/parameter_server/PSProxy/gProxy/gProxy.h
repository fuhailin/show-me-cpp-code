/*
 * @Company: TWL
 * @Author: gu shitao
 * @Email: gushitao@kanzhun.com
 * @Date: 2019-10-23 14:40:33
 */

/*
 *切换规则：
 *   gProxy_Failed：控制失败次数
 *   gProxy_Succ：控制成功次数
 *   m_switchoverCheckTimes：没多少次成功与失败的和算一个检查周期
 *   m_switchoverSucc：一个检查周期内多少次成功则不需要切换
 *   eg:
 *       假设m_switchoverCheckTimes = 10， m_switchoverSucc = 7，则成功7次时，
 *   失败次数<=3则不需要切换，统计计数器清零。若失败次数>=3，则进行主备切换，统计计
 *   数器清零，
 *
 */



#ifndef _GPROXY_H_
#define _GPROXY_H_

// 主备切换信息
#define PRINT_SWITCHOVER_INFO

// 机器下线信息
#define PRINT_DELETE_INFO

// 普通信息
//#define PRINT_INFO


#include "ParaServ.h"
#include <atomic>
#include <boost/algorithm/string.hpp>
#include <condition_variable>
#include <map>
#include <mutex>
#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <iostream>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "nlohmann/json.hpp"
#include "zkclient.h"
#include "RWLock.h"
#include "gcommon.h"
#include "logger.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace std;
// 调用客户端方法时返回值
enum RETURN_CODE_USE_PROXY {
	PROXY_SUCCESS = 0, // 操作成功
	PROXY_NO_CONNECT, // 无服务在线
    PROXY_CONNECT_ERROR, // 连接异常(多数为超时)
    PROXY_UNKNOWN, // 未知错误
    PROXY_CONNECT_OFFLINE, // 服务端下线
    PROXY_INPUT_ERROR, // 输入参数异常
};

#define GPROXY_NOT_POD(__OBJ__, __CLIENT_TYPE__, __INDEX__, __CLIENT_FUN__, __ARGS__)\
    int rc = -1;\
    bool master=true;\
    stConnectNode<__CLIENT_TYPE__>* p2connect = nullptr;\
    /* online read operations 50% -> slave*/ \
    if(std::string(#__CLIENT_FUN__)==std::string("pull_online")){\
        __OBJ__.serial++;\
        if(__OBJ__.serial % 2==0){\
            master=false;\
            p2connect = __OBJ__.getConnect(__INDEX__, master);\
        } else {\
            p2connect = __OBJ__.getConnect(__INDEX__, master);\
        }\
    } else {\
        p2connect = __OBJ__.getConnect(__INDEX__, master); \
    }\
    if(p2connect == nullptr)\
    {\
        std::cout<<"--no connect"<<std::endl;\
        if(master==true)\
            __OBJ__.gProxy_Failed(__INDEX__);\
        rc = PROXY_NO_CONNECT;\
    }\
    else\
    {\
        shared_ptr<mutex> mtx = p2connect->connectMutex;\
        shared_ptr<condition_variable> cond = p2connect->connectCondition;\
        shared_ptr<int> status = p2connect->status;\
        bool delete_conn=false;\
        {\
            unique_lock<mutex> u(*mtx);\
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});\
            try\
            {\
                if(*status == GPROXY_CONNECT_OK)\
                {\
                    *status = GPROXY_CONNECT_USING;\
                    p2connect->client->__CLIENT_FUN__ __ARGS__;\
                    *status = GPROXY_CONNECT_OK;\
                    if(master==true)\
                        __OBJ__.gProxy_Succ(__INDEX__);\
                    cond->notify_one();\
                    rc = PROXY_SUCCESS;\
                }\
                else\
                {\
                    std::cout<<"--proxy conn not ok"<<std::endl;\
                    cond->notify_one();\
                    rc = PROXY_CONNECT_OFFLINE;\
                }\
            }\
            catch(apache::thrift::transport::TTransportException& e)\
            {\
                std::cout<<"--thrift::transport exception:"<<e.what()<<std::endl;\
                *status = GPROXY_CONNECT_OFFLINE;\
                delete_conn=true;\
                if(master==true)\
                    __OBJ__.gProxy_Failed(__INDEX__);\
                cond->notify_one();\
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))\
                    rc = PROXY_CONNECT_OFFLINE;\
                else\
                    rc = PROXY_CONNECT_ERROR;\
            }\
            catch(std::exception& e)\
            {\
                std::cout<<"--exception:"<<e.what()<<std::endl;\
                *status = GPROXY_CONNECT_OK;\
                cond->notify_one();\
                if(strstr(e.what(), "failed: unknown result"))\
                    rc = PROXY_INPUT_ERROR;\
                else\
                    rc = PROXY_UNKNOWN;\
            }\
        }\
        if(delete_conn) __OBJ__.deleteConnect(__INDEX__, p2connect->connectNodeKey, master);\
    }\
    delete &__INDEX__;\
    return rc




#define GPROXY_SLAVE_NOT_POD(__CLIENT_TYPE__, __INDEX__, __CLIENT_FUN__, __ARGS__)\
    int rc = -1;\
    shared_ptr<stConnectNode<__CLIENT_TYPE__>> p2connect = m_connectPool[__INDEX__].slaveConnect;\
    if(p2connect == nullptr)\
    {\
        rc = PROXY_NO_CONNECT;\
    }\
    else\
    {\
        shared_ptr<mutex> mtx = p2connect->connectMutex;\
        shared_ptr<condition_variable> cond = p2connect->connectCondition;\
        shared_ptr<int> status = p2connect->status;\
        {\
            unique_lock<mutex> u(*mtx);\
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});\
            try\
            {\
                if(*status == GPROXY_CONNECT_OK)\
                {\
                    *status = GPROXY_CONNECT_USING;\
                    p2connect->client->__CLIENT_FUN__ __ARGS__;\
                    *status = GPROXY_CONNECT_OK;\
                    cond->notify_one();\
                    rc = PROXY_SUCCESS;\
                }\
                else\
                {\
                    cond->notify_one();\
                    rc = PROXY_CONNECT_ERROR;\
                }\
            }\
            catch(apache::thrift::transport::TTransportException& e)\
            {\
                p2connect->transport->close();\
                WriteGuard w(*(m_connectPool[__INDEX__].masterSlaveNode_rwmtx));\
                m_connectPool[__INDEX__].slave_ip = "";\
                m_connectPool[__INDEX__].slave_port = -1;\
                m_connectPool[__INDEX__].slaveConnect = nullptr;\
                rc = PROXY_CONNECT_ERROR;\
            }\
            catch(std::exception& e)\
            {\
                *status = GPROXY_CONNECT_OK;\
                cond->notify_one();\
                rc = PROXY_UNKNOWN;\
            }\
        }\
    }

// 链接池默认下标
#define DEFAULT_INDEX -1

using std::string;
using std::stoi;
using std::to_string;
using std::vector;
using std::pair;
using std::set;
using std::map;
using std::move;
using std::mutex;
using std::lock_guard;
using std::shared_ptr;
using std::thread;
using std::condition_variable;
using std::unique_lock;
using std::unordered_map;
using std::atomic_ullong;
using json = nlohmann::json;

using TTransportSharedPtr = ::apache::thrift::stdcxx::shared_ptr<TTransport>;

// 连接状态机
enum GPROXY_CONNECT_STATUS {
	GPROXY_CONNECT_OK = 0,     // 正常
    GPROXY_CONNECT_USING,      // 使用中
    GPROXY_CONNECT_OFFLINE,    // 下线
};

// 连接池结点
template <class T>
struct stConnectNode
{
    int index;                              // 连接池vec的index
    std::string connectNodeKey;      // 形如1234_x
    TTransportSharedPtr transport;                       // for close
    shared_ptr<T>       client;                // 服务客户端
    shared_ptr<mutex> connectMutex;
    shared_ptr<condition_variable> connectCondition;
    shared_ptr<int> status;                             // 0空闲，1使用中，2销毁
    stConnectNode():
        index(-1),
        client(nullptr),
        connectMutex(new mutex),
        connectCondition(new condition_variable),
        status(new int(0))
    {
    }
};


// 主从信息结点
struct stMasterSlaveInfoNode
{
    string groupid;
    string master_ip;
    int master_port;
    string slave_ip;
    int slave_port;
    int master;
    int slave;

    stMasterSlaveInfoNode(const string& gid, const string& mip, const int& mport):
        groupid(gid),
        master_ip(mip),
        master_port(mport),
        slave_ip(""),
        slave_port(-1),
        master(-1),
        slave(-1)
    {
    }

    stMasterSlaveInfoNode(const string& sip, const int& sport, const string gid):
        groupid(gid),
        master_ip(""),
        master_port(-1),
        slave_ip(sip),
        slave_port(sport),
        master(-1),
        slave(-1)
    {
    }
};

// 主从结构连接池结点
template <class T>
struct stMasterSlaveNode
{
    string groupid;//组id
    int step;

    string master_ip;
    int master_port;
    map<std::string, stConnectNode<T>> masterPool;
    map<std::string, stConnectNode<T>> slavePool;
    string slave_ip;
    int slave_port;
    shared_ptr<stConnectNode<T>> slaveConnect;

    shared_ptr<RWLock> masterSlaveNode_rwmtx;// 读写锁
    shared_ptr<atomic_ullong> ptr_failed_count;         // 单位时间内使用次数
    shared_ptr<atomic_ullong> ptr_success_count;       // 单位时间内成功次数
    int master;
    int slave;

    stMasterSlaveNode(const string& groupId, const string& ip, int port):
        groupid(groupId),
        step(0),
        master_ip(ip),
        master_port(port),
        slave_ip(""),
        slave_port(-1),
        slaveConnect(nullptr),
        masterSlaveNode_rwmtx(new RWLock),
        ptr_failed_count(new atomic_ullong(0)),
        ptr_success_count(new atomic_ullong(0)),
        master(-1),
        slave(-1)
    {
    }

};

enum gProxyErrorCode {
    GPROXY_ERROR_SUCCESS_RATE = -3,
    GPROXY_ERROR_INIT = -2,
    GPROXY_ERROR_CREATE_MASTER = -1,
	GPROXY_SUCCESS = 0,
};

template <class T>
class gProxy
{
public:
    gProxy(const string zkHost,
            const string zkPath,
            const int masterNumber=3,
            const int psTimeout = 1000 * 2,
            const int successRate = 70,
            const int switchoverCheckTimes = 5,
            const bool checkOnline = false,
            const int zkTimeout = 1000 * 10, const double backgroundThreadCheckTimes=1.0/*默认值全为拍脑袋想的*/,
            const int slaveSpecialInfo = -1):
        m_zkHost(zkHost),
        m_zkPath(zkPath),
        m_masterNumber(masterNumber),
        m_successRate(successRate),
        m_switchoverCheckTimes(switchoverCheckTimes),
        m_switchoverSucc(successRate*switchoverCheckTimes/100),
        m_zkTimeout(zkTimeout),
        m_suffix(0),
        m_ptrBackgroundThread(nullptr),
        m_ptrSwitchoverThread(nullptr),
        m_threadRun(true),
        m_backgroundThreadCheckTimes(backgroundThreadCheckTimes),
        m_checkOnline(checkOnline),
        m_online(true),
        m_slaveSpecialInfo(slaveSpecialInfo),
        m_psTimeout(psTimeout)
    {
    }
//protected:
    /*
    */
    int gProxyInit();

//protected:
    /*
    * 【主线程接口】【纯虚函数】创建链接节点并挂在连接池上
    */
    virtual void createConnect(stConnectNode<T>& connectNode, const string& ip, const int port) = 0;

    /*
    * 【主线程接口】为thrift客户端返回一个连接
    */
    stConnectNode<T>* getConnect(const int index, bool &master);

    /*
    *【主线程接口】删除指定链接
    * [0 池找链, 1 链找点, 2 删除点]
    * 池找链
    */
    void deleteConnect(const int index, const std::string connectNodeKey, const bool master);

    /*
    * 【主线程接口】使用链接成功
    */
    void gProxy_Succ(int index);

    /*
    * 【主线程接口】使用链接失败
    */
    void gProxy_Failed(int index);

    /*
    * 【主线程接口】返回链接组数
    */
    int getGroupNumber();
private:
    /*
    * 【后台线程接口】向各个连接池中加客户端
    */
    void addClient2ConnectPool();

private:
    /*
    * 删除点
    */
    bool deleteConnect_2(stConnectNode<T>& delete_connectNode, const char* deleteMsg, const bool inLock=true);

    /*
    * 链找点
    */
    void deleteConnect_1(stMasterSlaveNode<T>& masterSlaveNode, std::string connectNodeKey, const bool master);

    /*
    * 创建主备切换线程
    */
    void createSwitchoverThread();
    void switchoverThread();
    void doSwitchover(stMasterSlaveNode<T>& masterSlaveNode, const int index);

    /*
    * 判断是否需要进行主备切换
    */
    bool needSwitchover();

    /*
    * 初始化连接池
    */
    void initConnectPool();

    /*
    * 获取zk中groupid、机器号、ip、端口信息
    */
    void getGroupidIpPort();
    void getIpPort(const string& zkPath, string& ip, int& port);

    /*
    * 创建连接池
    */
    void doCreateConnectPool();
    void createConnectPool(stMasterSlaveInfoNode& masterSlaveInfoNode, const int index=DEFAULT_INDEX);

    /*
    * 创建主节点链
    */
    int connectMaster(const stMasterSlaveInfoNode& msiNode/*masterSlaveInfoNode*/, const int index);
    void createMasterPool(map<std::string, stConnectNode<T>>& masterPool, const string groupid, const string ip, const int port, const int index);

    /*
    * 创建从节点
    */
    void connectSlave(const int index, const stMasterSlaveInfoNode& msiNode/*masterSlaveInfoNode*/);
    void createSlavePool(map<std::string, stConnectNode<T>>& slavePool, const string groupid, const string ip, const int port, const int index);
    /*
    * 创建后台监控线程，用于补充链接、检测备份心跳
    */
    void createBackgroudThread();
    void backgroudThreadFun();

    /*
    * 检测备份心跳
    */
    void slaveHeartbeat();

    /*
    * 检测主链接是否为空
    */
    void checkAllMasterOnline();

    /*
    * NAME: watchGetChildren:,子节点watch方法，监控zk变化
    * errcode
    * path
    * count :子节点个数
    * data :子节点名称字符串数组（* 遍历时需要用count控制，否则必炸）
    * context :调用时传入的数据(此处为this指针)
    */
    static void watchGetChildren(ZKErrorCode errcode, const std::string& path, int count, char** data, void* context);


public:
    virtual ~gProxy()
    {
        m_threadRun = false;

        // 关闭旁路线程
        if(m_ptrBackgroundThread)
        {
            m_ptrBackgroundThread->join();
            delete m_ptrBackgroundThread;
        }

        // 关闭主备切换线程
        if(m_ptrSwitchoverThread)
        {
            m_ptrSwitchoverThread->join();
            delete m_ptrSwitchoverThread;
        }

        for(auto& it_connectPool : m_connectPool)
        {
            for(auto& it: it_connectPool.masterPool)
            {
                it.second.transport->close();
            }
        }
    }


private:
    const string m_zkHost;  // zk服务地址
    const string m_zkPath;  // zk父节点路径
    const int m_masterNumber;// 主服务结点链接个数(每个连接池的建议最大长度)
    const int m_successRate;// 单位时间内成功率低于此值则切换
    const int m_switchoverCheckTimes; // 每几次返回结果检查一下是否切换
    const int m_switchoverSucc; // 成功次数 = m_successRate * m_switchoverCheckTimes / 100
    const int m_zkTimeout;    // zk初始化时的超时时间
    ZKClient m_zkClinet;    // zk连接句柄
    int m_suffix;           // 服务后缀，做唯一标识
    vector<stMasterSlaveInfoNode> m_masterSlaveInfo; // 记录主从的ip:port信息
    thread* m_ptrBackgroundThread;// 旁路线程
    thread* m_ptrSwitchoverThread; // 主备切换线程，每m_psTimeout秒检查一下是否需要切换
    bool m_threadRun;// 旁路线程是否运行参数，析构时会置为false
    const double  m_backgroundThreadCheckTimes;  // 后台线程每秒跑的次数
    condition_variable m_switchoverCond;        // 用来通知主备切换的条件变量
    const bool m_checkOnline;   // 是否检查服务是否在线
    bool m_online;              // 服务在线标志（m_checkOnline为true时，任意一个主结点全挂则认为整个gProxy服务不可用，getConnect返回为空）
    std::unordered_map<std::string, int> m_master_idx; //

private:
    const int m_slaveSpecialInfo;// 心跳时传入的特殊值（psProxy备机使用follow模式启动时，传入fileNum值）

protected:
    const int m_psTimeout;  // ps服务超时时间，同时作为主备切换的窗口时间（单位秒，不足一秒按一秒算），单位毫秒

protected:
    vector<stMasterSlaveNode<T>> m_connectPool;
};


/*
********************************************************************************
************** 派生类调用的模板方法不支持分离编译，必须在声明的文件里实例化 **************
********************************************************************************
*/

/*
* 【主线程接口】为thrift客户端返回一个连接
*/
template <class T>
stConnectNode<T>* gProxy<T>::getConnect(const int index, bool& master)
{
    stConnectNode<T>* p2connect = nullptr;

    if(index >= m_connectPool.size() || index < 0)
    {
        p2connect = nullptr;
    }
    // 如果需要检查并且为下线状态，直接返回nullptr
    if(m_checkOnline && !m_online)
    {
#ifdef PRINT_INFO
        logger->info("[gProxy]getConnect|some server is offline|");
#endif
        p2connect = nullptr;
    }
    else
    {
        auto& connectPool = m_connectPool[index];
        ReadGuard r(*(connectPool.masterSlaveNode_rwmtx));

        map<std::string, stConnectNode<T>>* connectionMap = nullptr;

        if (master == false && connectPool.slavePool.size() > 0) {
            connectionMap = &connectPool.slavePool;
        } else {
            master = true;
            connectionMap = &connectPool.masterPool;
        }

        int connectPoolSize = static_cast<int>(connectionMap->size());
        if(connectPoolSize < 1)
        {
            p2connect = nullptr;
        }
        else
        {
            int pool_step = connectPool.step % connectPoolSize;
            auto it = connectionMap->begin();
            while(pool_step--) ++it;
            connectPool.step = connectPool.step > 12345 ? 0 : connectPool.step + 1;
            p2connect = &(it->second);
#ifdef PRINT_INFO
            logger->info("[gProxy]getConnect|index={}|groupid={}|{}|{}:{}|",
                    index, m_connectPool[index].groupid.data(), it->first.data(),
                    m_connectPool[index].master_ip.data(), m_connectPool[index].master_port);
#endif
        }
    }
    return p2connect;
}




template <class T>
int gProxy<T>::gProxyInit()
{
    if(m_successRate<0 || m_successRate>99)
    {
        return GPROXY_ERROR_SUCCESS_RATE;
    }
    // 初始化zk连接
    if (!m_zkClinet.Init(m_zkHost.c_str(), m_zkTimeout))
    {
        return GPROXY_ERROR_INIT;
    }
    initConnectPool();
    createBackgroudThread();
    createSwitchoverThread();
    return static_cast<int>(m_connectPool.size());
}




template <class T>
void gProxy<T>::addClient2ConnectPool()
{
    for(int i = 0; i < m_connectPool.size(); ++i)
    {
        auto& it = m_connectPool[i];
        if(it.masterPool.size() < m_masterNumber)
        {
            WriteGuard w(*(it.masterSlaveNode_rwmtx));
            int number = m_masterNumber - it.masterPool.size();
            try
            {
                while(number--)
                {
                    logger->info("addClient2ConnectPool start");
                    stConnectNode<T> connectNode;
                    createConnect(connectNode, it.master_ip, it.master_port);
                    connectNode.index = i;
                    connectNode.connectNodeKey = it.groupid+"_"+to_string(m_suffix++);
                    it.masterPool.insert(pair<std::string, stConnectNode<T>>(connectNode.connectNodeKey, move(connectNode)));
                    logger->info("[gProxy]addClient|index={}|groupid={}|{}|{}:{}|", i, it.groupid.data(),
                                 (it.groupid+"_"+to_string(m_suffix-1)).data(), it.master_ip.data(), it.master_port);
                    logger->info("addClient2ConnectPool end");
                }
            }
            catch(...)
            {
                gProxy_Failed(i);
                // 异常后不做任何，尝试number为止
            }
        }
    }
}

template <class T>
void gProxy<T>::doSwitchover(stMasterSlaveNode<T>& masterSlaveNode, const int index)
{
    string master_ip;
    string old_master_ip_port;
    int master_port;

    {
        ReadGuard r(*(masterSlaveNode.masterSlaveNode_rwmtx));
        if(masterSlaveNode.slave_ip.empty() || masterSlaveNode.slave_port == -1)
        {
            // 无备份节点，后续需要告警

#ifdef PRINT_SWITCHOVER_INFO
            logger->info("[gProxy]doSwitchover falied(slave info is empty)|groupid={}|index={}|",
                        masterSlaveNode.groupid.data(), index);
#endif
            return;
        }
        old_master_ip_port = masterSlaveNode.master_ip+":"+std::to_string(masterSlaveNode.master_port);
        master_ip = move(masterSlaveNode.slave_ip);
        master_port = masterSlaveNode.slave_port;

        masterSlaveNode.slave_ip = "";
        masterSlaveNode.slave_port = -1;
    }

    // 创建旧的主备链接临时节点，用于下线
    map<std::string, stConnectNode<T>> old_masterPool;
    shared_ptr<stConnectNode<T>> old_slaveConnect;

    // 2.备升主，删除备份信息
    // 链接暂时不断，因为断链接需要加链接上的写锁，可能会存在短暂阻塞
    {
        WriteGuard w(*(masterSlaveNode.masterSlaveNode_rwmtx));
        old_masterPool = move(masterSlaveNode.masterPool);
        masterSlaveNode.masterPool = move(masterSlaveNode.slavePool);
        masterSlaveNode.master_ip = master_ip;
        masterSlaveNode.master_port = master_port;
        masterSlaveNode.master = masterSlaveNode.slave;
        // 删除备份信息
        old_slaveConnect = masterSlaveNode.slaveConnect;
        masterSlaveNode.slaveConnect = nullptr;// 这有此处写操作，无需加锁
        masterSlaveNode.slave = -1;
    }

    // 删除原来的主链接
    for(auto it = old_masterPool.begin();
        it != old_masterPool.end();
        it = old_masterPool.begin())// 并发删除场景需要重置迭代器，所以不用传统的old_masterPool.erase(it++);
    {
        char buf[128] = {0};
        snprintf(buf, sizeof(buf), "[gProxy]deleteConnect(switchover)|groupid=%s|delete old master %s|%s:%d|\n",
            masterSlaveNode.groupid.data(), it->first.data(), master_ip.data(), master_port);
        deleteConnect_2(it->second, buf, false);
        old_masterPool.erase(it);// 并发删除场景需要重置迭代器，所以不用传统的old_masterPool.erase(it++);
    }

    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "[gProxy]deleteConnect(switchover)|groupid=%s|delete keep alive|%s:%d|\n",
        masterSlaveNode.groupid.data(), masterSlaveNode.slave_ip.data(), masterSlaveNode.slave_port);
    // 删除原来的备份链接
    deleteConnect_2(*old_slaveConnect, buf, false);

    //手动清除原master节点的zk信息，确保所有psProxy进行主从切换，避免psProxy存在主从不一致的情况
    string old_master_path = m_zkPath +"/"+masterSlaveNode.groupid+"/"+std::to_string(m_master_idx[masterSlaveNode.groupid]);
    //std::cout<<"============old_master_path============================"<<old_master_path<<std::endl;
    m_zkClinet.Delete(old_master_path, gcommon::TestDeleteHandler,NULL);
    ++m_master_idx[masterSlaveNode.groupid];

    std::string proxy;
    proxy = "psProxy_ip: " +gcommon::getIp();
    std::string alert_command = "curl \"https://oapi.dingtalk.com/robot/send?access_token=05ca4dea0b988bdd00fff889c16e2bfb6cfda67ba2d9a87ecea7932d234df13b\" \
    -H \'Content-Type: application/json\' \
    -d \'{\"msgtype\": \"text\", \"text\": { \"content\": \"报警：doSwitchover! \n"+proxy+"\n psServer_ip: "
    + old_master_ip_port+"\n zk_path: "+old_master_path+"\"}}\'";

    // int ret = system(alert_command.c_str());
    // if (ret!=0) {
    //     std::cout << "cmd exec failed" << std::endl;
    // }
    logger->info(">> switch over");
}

template <class T>
bool gProxy<T>::needSwitchover()
{
    for(auto& it : m_connectPool)
    {
        if(*(it.ptr_failed_count) >= m_switchoverCheckTimes-m_switchoverSucc)
            return true;
    }

    return false;
}

/*
* 【主线程接口】使用链接成功
*/
template <class T>
void gProxy<T>::gProxy_Succ(int index)
{
    if(index >= m_connectPool.size() || index < 0)
    {
        return;
    }

    // 若加1后达到统计切换的成功次数
    if((++(*(m_connectPool[index].ptr_success_count))) >= m_switchoverSucc)
    {
        if(*(m_connectPool[index].ptr_failed_count) < m_switchoverCheckTimes - m_switchoverSucc)
        {

            // 若此时失败次数小于 检查次数-成功次数，则统计计数器清零，开始下一轮统计
            *(m_connectPool[index].ptr_failed_count) = *(m_connectPool[index].ptr_success_count) = 0;

#ifdef PRINT_INFO
            string strNow(gcommon::now());
            if(failed+success)
            {
                int success_rate = static_cast<int>((success * 10000)/(failed+success));
                int success_rate1 = success_rate / 100;
                int success_rate2 = success_rate % 100;
                logger->info("[gProxy]check switchover|index={}|groupid={}|"
                    "{}|"
                    "success rate bar({})|"
                    "req={}, succ={}|"
                    "success rate=({}.{})",
                    index, m_connectPool[index].groupid.data(),
                    strNow.substr(0,19).data(),
                    m_successRate,
                    failed+success, success,
                    success_rate1, success_rate2);
            }
            else
            {
                logger->info("[gProxy]check switchover|index={}|groupid={}|"
                    "{}|"
                    "switchover rate({})|"
                    "req=0, succ=0|"
                    "pass",
                    index, m_connectPool[index].groupid.data(),
                    strNow.substr(0,19).data(), m_successRate);
            }
#endif
        }
        else
        {
            // 通知进行主备切换
            m_switchoverCond.notify_one();
        }
    }
}


/*
* 【主线程接口】使用链接失败
*/
template <class T>
void gProxy<T>::gProxy_Failed(int index)
{
    if(index >= m_connectPool.size() || index < 0)
    {
        return;
    }

    // 若加1后达到切换的失败次数
    if((++(*(m_connectPool[index].ptr_failed_count))) >= m_switchoverCheckTimes-m_switchoverSucc)
    {
        // 通知进行主备切换
        m_switchoverCond.notify_one();
    }
}


template <class T>
void gProxy<T>::switchoverThread()
{
    mutex mtx;
    while(m_threadRun)
    {
        unique_lock<mutex> ul(mtx);
        while(m_threadRun && !needSwitchover())
        {
            // 必须使用wait_for，否则获取到ctrl+c后进程仍无法退出
            m_switchoverCond.wait_for(ul, std::chrono::seconds(1));
        }

        if(!m_threadRun)
            break;

        for(int i = 0 ; i < m_connectPool.size(); ++i)
        {
            unsigned long long failed = *(m_connectPool[i].ptr_failed_count);
            unsigned long long success = *(m_connectPool[i].ptr_success_count);

            if(failed >= m_switchoverCheckTimes-m_switchoverSucc)
            {
#ifdef PRINT_SWITCHOVER_INFO
                int success_rate = static_cast<int>((success * 10000)/(failed+success));
                int success_rate1 = success_rate / 100;
                int success_rate2 = success_rate % 100;
                string strNow(gcommon::now());
                logger->info("[gProxy]skip doSwitchover|index={}|groupid={}|"
                        "{}|"
                        "req={} succ={}|"
                        "success rate=({}.{}), less than switchover success rate({})",
                        i, m_connectPool[i].groupid.data(),
                        strNow.substr(0,19).data(),
                        failed+success, success,
                        success_rate1, success_rate2, m_successRate);
#endif
                //暂时屏蔽主动触发的主备切换
                //doSwitchover(m_connectPool[i], i);
            }

            // 统计计数器清零
            *(m_connectPool[i].ptr_success_count) = *(m_connectPool[i].ptr_failed_count) =0;
        }
    }
}

template <class T>
void gProxy<T>::backgroudThreadFun()
{
    while(m_threadRun)
    {
        // 补充链接
        addClient2ConnectPool();

        // 检查ps服务是否正常在线
        checkAllMasterOnline();

        // 备机保活
        slaveHeartbeat();

        if(m_threadRun)
            usleep(static_cast<int>(1000 * 1000 / m_backgroundThreadCheckTimes));
    }
}


template <class T>
void gProxy<T>::slaveHeartbeat()
{
    static int cnt = 1000000;
    static int groupNumber = getGroupNumber();
    static string ret;
    for(int i = 0; i < groupNumber; ++i)
    {
        if(m_connectPool[i].slaveConnect)
        {
#ifdef PRINT_DELETE_INFO
            string slave_ip = m_connectPool[i].slave_ip;
            int slave_port = m_connectPool[i].slave_port;
#endif
            int input = m_slaveSpecialInfo == -1 ? cnt : m_slaveSpecialInfo;
            GPROXY_SLAVE_NOT_POD(T, i, heartbeat, (ret, input));
            ++cnt;
            if(rc == PROXY_SUCCESS)
            {
#ifdef PRINT_INFO
                logger->info("[gProxy]slaveHeartbeat|index={}|groupid={}|{}:{}|",
                    i, m_connectPool[i].groupid.data(), m_connectPool[i].slave_ip.data(), m_connectPool[i].slave_port);
#endif
            }
            else
            {
#ifdef PRINT_DELETE_INFO
                logger->info("[gProxy][falied rc={}]slaveHeartbeat|index={}|groupid={}|{}:{}|",
                    rc, i, m_connectPool[i].groupid.data(), slave_ip.data(), slave_port);
#endif
            }
        }
    }

    cnt = cnt > 1000000 + 12345 ? 1000000 : cnt;
}


template <class T>
void gProxy<T>::createSwitchoverThread()
{
    m_ptrSwitchoverThread = new thread(&gProxy::switchoverThread, this);
}


template <class T>
void gProxy<T>::createBackgroudThread()
{
    m_ptrBackgroundThread = new thread(&gProxy::backgroudThreadFun, this);
}

template <class T>
void gProxy<T>::initConnectPool()
{
    // 构造m_masterSlaveInfo
    getGroupidIpPort();
    doCreateConnectPool();
}

template <class T>
void gProxy<T>::createMasterPool(map<std::string, stConnectNode<T>>& masterPool, const string groupid, const string ip, const int port, const int index)
{
    int number = m_masterNumber;//尝试创建client个数
    try
    {
        while(number--)
        {
            stConnectNode<T> connectNode;
            createConnect(connectNode, ip, port);
            connectNode.index = index;
            connectNode.connectNodeKey = groupid+"_"+to_string(m_suffix++);
            masterPool.insert(pair<std::string, stConnectNode<T>>(connectNode.connectNodeKey, move(connectNode)));
        }
    }
    catch(...)
    {
        // 异常后不做任何，尝试number为止
    }
}

template <class T>
void gProxy<T>::createSlavePool(map<std::string, stConnectNode<T>>& slavePool, const string groupid, const string ip, const int port, const int index)
{
    map<std::string, stConnectNode<T>> pool;
    int number = m_masterNumber;//尝试创建client个数
    try
    {
        while (number--)
        {
            stConnectNode<T> connectNode;
            createConnect(connectNode, ip, port);
            connectNode.index = index;
            connectNode.connectNodeKey = groupid + "_" + to_string(m_suffix++);
            pool.insert(pair<std::string, stConnectNode<T>>(connectNode.connectNodeKey, move(connectNode)));
        }
    }
    catch (...)
    {
        // 异常后不做任何，尝试number为止
    }
    slavePool = move(pool);
}

template <class T>
int gProxy<T>::connectMaster(const stMasterSlaveInfoNode& msiNode, const int index)
{
    stMasterSlaveNode<T> masterSlaveNode(msiNode.groupid, msiNode.master_ip, msiNode.master_port);

    createMasterPool(masterSlaveNode.masterPool, msiNode.groupid, msiNode.master_ip, msiNode.master_port,
                        index == DEFAULT_INDEX ? static_cast<int>(m_connectPool.size()) : index);

    int rc = GPROXY_ERROR_CREATE_MASTER;
    if(masterSlaveNode.masterPool.size() > 0)
    {
        // 初始化创建主链接
        if(index == DEFAULT_INDEX)
        {
            m_connectPool.emplace_back(move(masterSlaveNode));
            rc = m_connectPool.size() - 1;
        }
        // 运行中补充主链接
        else
        {
            m_connectPool[index].master_ip = move(msiNode.master_ip);
            m_connectPool[index].masterPool = move(masterSlaveNode.masterPool);
            m_connectPool[index].master_port = move(msiNode.master_port);
            m_connectPool[index].master = msiNode.master;
            rc = index;
        }

    }
    return rc;
}

template <class T>
void gProxy<T>::connectSlave(const int index, const stMasterSlaveInfoNode& msiNode/*masterSlaveInfoNode*/)
{
    // 只有主节点上线
    if(msiNode.slave_ip.empty() || msiNode.slave_port == -1)
    {
        return;
    }

    auto& masterSlaveNode=m_connectPool[index];
    createSlavePool(masterSlaveNode.slavePool, msiNode.groupid, msiNode.slave_ip, msiNode.slave_port,
        index == DEFAULT_INDEX ? static_cast<int>(m_connectPool.size()) : index);

    shared_ptr<stConnectNode<T>> slaveConnect(new(stConnectNode<T>));
    try
    {
        createConnect(*slaveConnect, msiNode.slave_ip, msiNode.slave_port);
    }
    catch(...)
    {
        // 异常后直接返回，此groupid的服务属于没有备机的情况
        return;
    }

    m_connectPool[index].slave_ip = msiNode.slave_ip;
    m_connectPool[index].slave_port =  msiNode.slave_port;
    m_connectPool[index].slave = msiNode.slave;
    m_connectPool[index].slaveConnect = slaveConnect;
#ifdef PRINT_INFO
            logger->info("[gProxy]connectSlave|index={}|groupid={}|{}:{}|\n"
                index, msiNode.groupid.data(), msiNode.slave_ip.data(), msiNode.slave_port);
#endif
}

template <class T>
void gProxy<T>::createConnectPool(stMasterSlaveInfoNode& masterSlaveInfoNode, const int index)
{
    int rc = connectMaster(masterSlaveInfoNode, index);

    // 创建主节点成功才创建从结点
    if(rc != GPROXY_ERROR_CREATE_MASTER)
        connectSlave(rc, masterSlaveInfoNode);
}

template <class T>
void gProxy<T>::doCreateConnectPool()
{
    for(auto it : m_masterSlaveInfo)
    {
        createConnectPool(it);
    }
}


template <class T>
void gProxy<T>::watchGetChildren(ZKErrorCode errcode, const std::string& path, int count, char** data, void* context)
{
    gProxy *p2this = static_cast<gProxy *>(context);
    static std::vector<bool> is_slave_lose(p2this->m_connectPool.size(), true);
    vector<string> path_groupid;
    boost::split(path_groupid, path, boost::is_any_of("/"), boost::token_compress_on);

    string groupid = path_groupid[path_groupid.size()-1];
    string proxy = "psProxy_ip: " +gcommon::getIp();

    logger->info("watch children: count = {}", count);

    for (int a = 0; a < count; a++) {
        logger->info("data:  {}", data[a]);
    }

    if (count > 2)
    {
        return;
    }

    if(errcode == kZKSucceed)
    {
        for(int index=0 ; index < p2this->m_connectPool.size() ; ++index)
        {
            // 查找对应的groupid
            if(p2this->m_connectPool[index].groupid == groupid)
            {
                auto& it = p2this->m_connectPool[index];

                // 0主在，备不在
                if(it.masterPool.size() != 0 && it.slaveConnect == nullptr)
                {
                    if(count == 2)
                    {
                        int data0 = stoi(data[0]);
                        int data1 = stoi(data[1]);
                        string slave_node = data0 > data1 ? data[0] : data[1];
                        string ip;
                        int port;
                        p2this->getIpPort(path+"/"+slave_node, ip, port);
                        stMasterSlaveInfoNode onlySlave(ip, port, groupid);
                        p2this->connectSlave(index, onlySlave);
                        is_slave_lose[index] = true;
#ifdef PRINT_SWITCHOVER_INFO
                        logger->info("[gProxy]watchZK|add slave|groupid={}|index={}|{}:{}|\n",
                            groupid.data(), index, ip.data(), port);
#endif
                    }

                    if(count == 1 && is_slave_lose[index]){ // 只有主在，报一次错
                            std::string alert_command = "curl \"https://oapi.dingtalk.com/robot/send?access_token=05ca4dea0b988bdd00fff889c16e2bfb6cfda67ba2d9a87ecea7932d234df13b\" \
                            -H \'Content-Type: application/json\' \
                            -d \'{\"msgtype\": \"text\", \"text\": { \"content\": \"报警：Lost slave node! \n"+proxy+"\n zk_path: "+path+"\"}}\'";

                            // int ret = system(alert_command.c_str());
                            // if (ret!=0) {
                            //     std::cout << "cmd exec failed" << std::endl;
                            // }
                            is_slave_lose[index] = false;
                    }
                }
                // 1主备都不在
                else if(it.masterPool.size() == 0 && it.slaveConnect == nullptr)
                {
                    string ip;
                    int port;
                    int ret = GPROXY_ERROR_CREATE_MASTER;
                    // 只有主上线
                    if(count == 1)
                    {
                        p2this->getIpPort(path+"/"+data[0], ip, port);
                        stMasterSlaveInfoNode masterSlaveInfoNode(groupid, ip, port);
                        ret = p2this->connectMaster(masterSlaveInfoNode, index);
                    }
                    else
                    {
                        // 主备同时上线
                        // 0操作层面来说，主备上线一定有顺序，主上线之后就会触发，同时上线情况可能性不大
                        // 1若真的出现，只处理主，备由兜底线程处理（暂时没兜底线程，感觉并不需要xD）。

                        int data0 = stoi(data[0]);
                        int data1 = stoi(data[1]);
                        string slave_node = data0 > data1 ? data[0] : data[1];

                        p2this->getIpPort(path+"/"+slave_node, ip, port);
                        stMasterSlaveInfoNode masterSlaveInfoNode(groupid, ip, port);
                        ret = p2this->connectMaster(masterSlaveInfoNode, index);
                    }

#ifdef PRINT_SWITCHOVER_INFO
                    if(ret != GPROXY_ERROR_CREATE_MASTER)
                        logger->info("[gProxy]watchZK|add master|groupid={}|index={}|{}:{}|{} connect is running|\n",
                            groupid.data(), index, ip.data(), port, p2this->m_connectPool[index].masterPool.size());
#endif

                }

                // 主备都在，忽略
                else if(it.masterPool.size() != 0 && it.slaveConnect != nullptr)
                {
                    if(count == 1 && is_slave_lose[index]){ // 只有主在，报一次错
                        std::string alert_command = "curl \"https://oapi.dingtalk.com/robot/send?access_token=05ca4dea0b988bdd00fff889c16e2bfb6cfda67ba2d9a87ecea7932d234df13b\" \
                            -H \'Content-Type: application/json\' \
                            -d \'{\"msgtype\": \"text\", \"text\": { \"content\": \"报警：Lost slave node! \n"+proxy+"\n zk_path: "+path+"\"}}\'";

                            is_slave_lose[index] = false;
                            // int ret = system(alert_command.c_str());
                            // if (ret!=0) {
                            //     std::cout << "cmd exec failed" << std::endl;
                            // }
                    }
                }

                //这段代码主要对zk监控做了优化
                extern int gRunModle;
                bool alert = false;
                std::string alert_content;
                if (count==0) {
                    if (gRunModle == 1 /*SERVERING*/) {
                        logger->info(">> servering mode ps bugs. {} path: {}", proxy, path);
                        alert_content = "Lost PS group! \n" + proxy + "\n zk_path: " + path;
                        alert = true;
                    }
                    else if (gRunModle == 0)
                    {
                        logger->info(">> training mode ps bugs. proxy: {} path: {}", proxy, path);
                        alert_content = "Lost PS group! \n" + proxy + "\n zk_path: " + path;
                    }
                } else {
                    bool match_m = false, match_s = false;
                    int group_master = p2this->m_master_idx[groupid];
                    for (int a = 0; a < count; a++)
                    {
                        int node_serial = stoi(data[a]);
                        if(group_master==node_serial)
                            match_m = true;
                        else if (it.slave==node_serial)
                            match_s = true;
                    }
                    // debug
                    // std::cout << ">> m "<<match_m<<" s "<<match_s <<" master "<<it.master<<" slave "<<it.slave<< std::endl;
                    if (match_m&&match_s) {
                        //
                    } else if (!match_m&&match_s) {
                        p2this->doSwitchover(p2this->m_connectPool[index], index);
                        logger->info(">> slave is switched over to master.  {} path: {}", proxy, path);
                        alert_content = "doSwitchover! \n" + proxy + "\n zk_path: " + path;
                        alert = true;
                    } else if (match_m&&!match_s&&it.slave!=-1) {
                        logger->info(">> slave is shutdown. {} path: {}", proxy, path);
                        // alert_content = ">> slave is shutdown. " + proxy + " path:" + path;
                        if (1)
                        {
                            char buf[128] = {0};
                            WriteGuard r(*(it.masterSlaveNode_rwmtx));
                            auto iter = it.slavePool.begin();
                            while(iter != it.slavePool.end()) {
                                p2this->deleteConnect_2(iter->second, buf, false);
                                it.slavePool.erase(iter);
                                iter = it.slavePool.begin();
                            }
                            it.slave = -1;
                        }
                        alert_content = "Lost slave node! \n" + proxy + "\n zk_path: " + path;
                        // alert = true;
                    }
                    else if (match_m && !match_s && it.slave == -1)
                    {
                        if (count<2) {
                            logger->error(">> unexpected error");
                            break;
                        }
                        it.slave=stoi(data[1]);
                        logger->info(">> slave is online. {} path: {}", proxy, path);
                        // alert_content = ">> slave is online. " + proxy + " path:" + path;
                    }
                }
                if (alert) {
                    std::string alert_command = "curl \"https://oapi.dingtalk.com/robot/send?access_token=05ca4dea0b988bdd00fff889c16e2bfb6cfda67ba2d9a87ecea7932d234df13b\" \
                        -H \'Content-Type: application/json\' \
                        -d \'{\"msgtype\": \"text\", \"text\": { \"content\": \"报警：";

                    alert_command += alert_content;
                    alert_command += "\"}}\'";

                    int ret = system(alert_command.c_str());
                    if (ret!=0) {
                        logger->error("cmd exec failed");
                    }
                }
                break;
            }
        }
    } else {
        logger->info("ec = {}", errcode);
    }
}


template <class T>
void  gProxy<T>::getGroupidIpPort()
{
    // 获取groupid
    vector<string> vecGroupid;
    m_zkClinet.GetChildren(m_zkPath, &vecGroupid);

    // 构造m_masterSlaveInfo
    for(auto it : vecGroupid)
    {
        vector<string> vecSTRServerNumber;
        set<int> setServerNumber;// 使用set排序，编号小的是master，大的是slave

        // 监控子节点变化信息
        m_zkClinet.GetChildren(m_zkPath+"/"+it, &vecSTRServerNumber,
                                watchGetChildren, static_cast<void*>(this), true);

        // 每个group下只能有1或2个节点
        if(vecSTRServerNumber.size() == 0 || vecSTRServerNumber.size() > 2)
        {
            continue;
        }

        for(auto itr: vecSTRServerNumber)
        {
            setServerNumber.insert(stoi(move(itr)));
        }

        auto itSet = setServerNumber.begin();
        int master = *itSet; // 最小的为master
        if(m_master_idx.find(it) == m_master_idx.end())
            m_master_idx[it] = master;
        string ip;
        int port;
        getIpPort(m_zkPath+"/"+it+"/"+to_string(master), ip, port);
        stMasterSlaveInfoNode masterSlaveInfoNode(it, move(ip), port);
        masterSlaveInfoNode.master = master;

        // 存在slave
        if((++itSet) != setServerNumber.end())
        {
            int slave = *itSet;
            ip="";port=-1;
            getIpPort(m_zkPath+"/"+it+"/"+to_string(slave), ip, port);
            masterSlaveInfoNode.slave_ip = move(ip);
            masterSlaveInfoNode.slave_port = port;
            masterSlaveInfoNode.slave = slave;
        }
        m_masterSlaveInfo.emplace_back(masterSlaveInfoNode);
    }
}


/*
* 【主线程接口】返回链接组数
*/
template <class T>
int gProxy<T>::getGroupNumber()
{
    static int groupNumber = -1;
    if(groupNumber == -1)
    {
        groupNumber = static_cast<int>(m_connectPool.size());
    }
    return groupNumber;
}

template <class T>
bool gProxy<T>::deleteConnect_2(stConnectNode<T>& delete_connectNode, const char* deleteMsg, const bool inLock)
{
    bool ret = false;
    if(inLock)
    {
        if(delete_connectNode.transport)
            delete_connectNode.transport->close();
        ret = true;
#ifdef PRINT_DELETE_INFO
            logger->info("{}", deleteMsg);
#endif
    }
    else
    {
        shared_ptr<mutex> mtx = delete_connectNode.connectMutex;
        shared_ptr<condition_variable> cond = delete_connectNode.connectCondition;
        shared_ptr<int> status = delete_connectNode.status;
        {
            unique_lock<mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            if(*status == GPROXY_CONNECT_OK)
            {
                *status = GPROXY_CONNECT_OFFLINE;
                if(delete_connectNode.transport)
                    delete_connectNode.transport->close();
                ret = true;

#ifdef PRINT_DELETE_INFO
                logger->info("{}", deleteMsg);
#endif

            }
            //else ret = false; // ret已经初始化为false
            cond->notify_all();
        }
    }


    return ret;
}

//1 链找点
template <class T>
void gProxy<T>::deleteConnect_1(stMasterSlaveNode<T>& masterSlaveNode, std::string connectNodeKey, const bool master)
{
    // 链可以被删除(主备切换), 需要加该链的写锁
    WriteGuard w(*(masterSlaveNode.masterSlaveNode_rwmtx));

    map<std::string, stConnectNode<T> > *connPool;
    std::string nodeType,ip;
    int port;

    if(master) {
        connPool = &masterSlaveNode.masterPool;
        nodeType = "master";
        ip = masterSlaveNode.master_ip;
        port = masterSlaveNode.master_port;
    }
    else
    {
        connPool = &masterSlaveNode.slavePool;
        nodeType = "slave";
        ip = masterSlaveNode.slave_ip;
        port = masterSlaveNode.slave_port;
    }
    auto conn = connPool->find(connectNodeKey);
    // 链找点
    if(connPool->empty() || connectNodeKey.empty()
        || conn == connPool->end())
    {
        // 没找到
        return;
    }

    char buf[128] = {0};
    snprintf(buf, sizeof(buf), "[gProxy]deleteConnect|groupid=%s|nodekey %s|node %s:%d\n",
            masterSlaveNode.groupid.data(), connectNodeKey.data(), ip.data(), port);

    if(deleteConnect_2(conn->second, buf))// 删除
    {
        connPool->erase(connectNodeKey);
    }

}

//0 池找链
template <class T>
void gProxy<T>::deleteConnect(const int index, const std::string connectNodeKey, const bool master)
{
    // 池找链
    if(index >= m_connectPool.size() || index < 0)
    {
        // 没找到
        return ;
    }

    deleteConnect_1(m_connectPool[index], connectNodeKey, master);// 链找点
}

template <class T>
void gProxy<T>::getIpPort(const string& zkPath, string& ip, int& port)
{
    char szBuf[4096*10] = {0};
    int iLength = (int)sizeof(szBuf);
    m_zkClinet.GetNode(zkPath, szBuf, &iLength);
    auto jZkInfo = json::parse(szBuf);
    ip = jZkInfo["ip"];
    port = jZkInfo["port"];
}

/*
* 检测主链接是否为空
*/
template <class T>
void gProxy<T>::checkAllMasterOnline()
{
    if(m_checkOnline == false)
        return;

    for(auto& it : m_connectPool)
    {
        // 若有不在线的服务则将服务改为下线状态
        if(it.masterPool.size() == 0)
        {
#ifdef PRINT_SWITCHOVER_INFO
            logger->info("[gProxy]checkAllMasterOnline|groupid={}|NO SERVER ONLINE!!!|\n",
                it.groupid.data());
#endif
            m_online = false;
            return;
        }
    }

#ifdef PRINT_SWITCHOVER_INFO
    if(m_online == false)
        logger->info("[gProxy]checkAllMasterOnline|SERVER RECOVER!!!|\n");
#endif

    m_online = true;
}

class Push{};
class SyncPush{};
class PushEmb{};
class PushAda{};

class Pull{};
class PullOnline{};

class Start{};
class CopyStart{};

class StartSync{};
class StopSync{};

class psProxy;

typedef int64_t Key;

template<typename T>
void PushFunc(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals) {
    logger->error("Error msg: you can't use the 'PushFunc' function!");
}

template<typename T>
void PullFunc(stConnectNode<ps::ParaServClient> *p2connect, map<Key, string> & _return, set<Key> & keys) {
    logger->error("Error msg: you can't use the 'PullFunc' function!");
}

template<typename T>
void StartFunc(stConnectNode<ps::ParaServClient> *p2connect, vector<int>& col_num, const int file_num) {
    logger->error("Error msg: you can't use the 'StartFunc' function!");
}

template<typename T>
void SyncFunc(stConnectNode<ps::ParaServClient> *p2connect, string& zkUrl, string& zkPath) {
    logger->error("Error msg: you can't use the 'SyncFunc' function!");
}

template<typename T>
void GetConnect(psProxy& obj,bool & master){
    logger->error("Error msg: you can't use the 'GetConnect' function!");
}

template<typename T>
void PsPushFunc(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals){
    logger->error("Error msg: you can't use the 'PsPushFunc' function!");
}

template<typename T>
void PsPullFunc(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & ret, set<Key> & splitKey){
    logger->error("Error msg: you can't use the 'PsPullFunc' function!");
}

template<>
void PsPushFunc<Push>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals);

template<>
void PsPushFunc<SyncPush>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals);

template<>
void PsPushFunc<PushEmb>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals);

template<>
void PsPushFunc<PushAda>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals);

template<>
void PsPullFunc<Pull>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & ret, set<Key> & splitKey);

template<>
void PsPullFunc<PullOnline>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & ret, set<Key> & splitKey);

template<>
void PushFunc<Push>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals);

template<>
void PushFunc<SyncPush>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals);

template<>
void PushFunc<PushEmb>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals);

template<>
void PushFunc<PushAda>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals);

template<>
void PullFunc<Pull>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, string> & _return, set<Key> & keys);

template<>
void PullFunc<PullOnline>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, string> & _return, set<Key> & keys);

template<>
void StartFunc<Start>(stConnectNode<ps::ParaServClient> *p2connect, vector<int>& col_num, const int file_num);

template<>
void StartFunc<CopyStart>(stConnectNode<ps::ParaServClient> *p2connect, vector<int>& col_num, const int file_num);

template<>
void SyncFunc<StartSync>(stConnectNode<ps::ParaServClient> *p2connect, string& zkUrl, string& zkPath);

template<>
void SyncFunc<StopSync>(stConnectNode<ps::ParaServClient> *p2connect, string& zkUrl, string& zkPath);

template<>
void GetConnect<PullOnline>(psProxy& obj,bool & master);

template<>
void GetConnect<Pull>(psProxy& obj,bool & master);

/*if (retry&&std::string(#__CLIENT_FUN__)==std::string("pull_online")){retry = false;goto ;}*/
template <typename Client>
int gproxy_heartbeat(psProxy& obj, int &index, string& ret, int input);

template <typename Client, typename FuncTag>
int gproxy_push(psProxy& obj, int &index, map<Key, std::string> & key_vals);

template <typename Client, typename FuncTag>
int gproxy_pull(psProxy& obj, int &index, map<Key, string> & _return, set<Key> & keys);

template <typename Client, typename FuncTag>
int gproxy_start(psProxy& obj, int &index, vector<int>& col_num, const int file_num);

template <typename Client>
int gproxy_transport(psProxy& obj, int &index, map<string, string> & col_num);

template <typename Client, typename FuncTag>
int gproxy_sync_client(psProxy& obj, int &index, string& zkUrl, string& zkPath);

template <typename Client>
int gproxy_status_cmd(psProxy& obj, int &index, string& reurn, string& cmd, std::vector<std::string> &values);

template <typename Client>
int gproxy_backup(psProxy& obj, int &index, std::string &ret, const std::string &type, const std::string &backup_name, map<string, string> & fileNum_ip);

template<typename FuncTag>
int ps_proxy_push(psProxy& obj, const map<Key, std::string> & key_vals);

template<typename FuncTag>
int ps_proxy_pull(psProxy& obj, map<Key, string>& _return, const set<Key>& keys);

#endif //_GPROXY_H_

