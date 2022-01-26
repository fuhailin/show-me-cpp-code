/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-11-11 10:19:27
 */
#ifndef _PS_PROXY_H_
#define _PS_PROXY_H_

#include "boost/asio.hpp"
#include "gProxy.h"
#include "tcmcp_psProxyServ.h"
#include <future>
#include <chrono>
#include "psProxy_module.h"

using std::future;
using std::packaged_task;
using std::ref;

using namespace ps;

// psProxy运行模式
enum PSPROXY_MODEL {
	TRAINING = 0, // 离线训练模式
	SERVERING, // 在线服务模式
    FOLLOW, // 跟随者模式
};

const int kFileNum = 24;   // 文件数目

class psProxy:public gProxy<ParaServClient>
{
public:
    /*
    * 构造函数
    *   zkHost:zookeeper url
    *   zkPath:zookeeper 信息路径
    *   poolSize 线程池大小
    *   masterNumber 每个ps结点的主节点个数
    *   checkOnline 是否开启单节点故障则拒绝服务的功能
    *   psTimeouts ps服务的超时时间
    *   successRate 成功率低于此值时进行主备切换
    *   switchoverCheckTimes 每switchoverCheckTimes次请求检查一次是否需要切换
    *   zkTimeout:zookeeper超时时间
    *   backgroundThreadCheckTimes 后台线程运行频率(维护备份心跳和增加主节点链接数)
    */
    psProxy(const string zkHost,
            const string zkPath,
            const int poolSize=5,
            const int masterNumber=3,
            const bool checkOnline=false,
            const bool force_copy_start=false,
            const int psTimeout=1000*2,
            const int successRate=70,
            const int switchoverCheckTimes=10,
            const int runModel = FOLLOW,
            const int fileNum = kFileNum,
            const int zkTimeout=1000*10, const double backgroundThreadCheckTimes=1.0/*默认值全为拍脑袋想的*/);

    /*
    * 初始化方法
    *   作用:
    *       0创建线程池
    *       1创建主备切换连接池gProxy
    *   返回值:
    *       ps服务启动组数（一旦确定，运行中不再改变，即使组中主机全部掉线。）
    */
    int init();

    /*
    *返回psProxy正常调用时的返回值
    *   返回值:psProxy正常调用时的返回值
    */
    int psProxyOK();

    int push(const map<Key, std::string> & key_vals);
    int sync_push(const map<Key, std::string> & key_vals);
    int pushemb(const map<Key, std::string> & key_vals);
    int pushada(const map<Key, std::string> & key_vals);
    int pull_online(map<Key, string> & _return, const set<Key> & keys);
    int pull(map<Key, string> & _return, const set<Key> & keys);
    int heartbeat(string& ret, int input);
    int backup(std::string &_return, const std::string &type, const std::string &directory);

    ~psProxy();

    bool force_copy_start() {return m_force_copy_start;}
    int copy_data(const map<string, string>& col_num);
    int replication(const string& zkUrl, const string& zkPath);
    int stop_replication(const string& zkUrl, const string& zkPath);
    int status_cmd(string& _return, const string& cmd, const std::vector<std::string>& values);

    int serial = 0;
// private:
    int runPsProxy();
    void createThreadpool();
    int psStart(const int i, vector<int>& col_num);
    int psCopyStart(const int i, vector<int>& col_num);
    string checkout_start(int& group);
    string get_start_status(int& group);
    string checkout_start_token_otherwise_wait_started();
    int set_all_started();

    void splite_keys(vector<set<Key>>& vecSpliteKeys, const set<Key>& keys);
    void splite_keys_vals(vector<map<Key, std::string>>& vecSpliteKeysVals, const map<Key, std::string> & key_vals);
    void createConnect(stConnectNode<ParaServClient>& connectNode, const string& ip, const int port);
    void createConnectToSlave(stConnectNode<ParaServClient>& connectNode, const string& ip, const int port);

    static int thread_push(psProxy& obj, int& index, map<Key, std::string> & key_vals);
    static int thread_sync_push(psProxy& obj, int& index, map<Key, std::string> & key_vals);
    static int thread_pushemb(psProxy& obj, int& index, map<Key, std::string> & key_vals);
    static int thread_pushada(psProxy& obj, int& index, map<Key, std::string> & key_vals);
    static int thread_pull_online(psProxy& obj, int& index, map<Key, string> & _return, set<Key> & keys);
    static int thread_pull(psProxy& obj, int& index, map<Key, string> & _return, set<Key> & keys);

    static int thread_psStart(psProxy& obj, int& i, vector<int>& col_num, int& file_num);
    static int thread_replication(psProxy& obj, int& index, string& zkUrl, string& zkPath);
    static int thread_stop_replication(psProxy& obj, int& index, string& zkUrl, string& zkPath);
    static int thread_transport(psProxy& obj, int& index, map<string, string> & col_num);
    static int thread_backup(psProxy &obj, int &index, std::string &ret, const std::string &type, const std::string &backup_name, map<string, string> &fileNum_ip);
    static int thread_status_cmd(psProxy &obj, int &index, std::string &_return, const std::string &cmd, const std::vector<std::string> &values);

    template <typename T, typename ...Args>
    future<T> post_task(T (*func)(Args&...), Args&... args)
    {
        packaged_task<T(Args&...)> task(func);
        future<T> ret = task.get_future();
        boost::asio::post(*m_threadpool, bind(move(task), ref(args)...));
        return ret;
    }
private:
    const int m_poolSize;// 线程池中线程个数
    shared_ptr<boost::asio::thread_pool> m_threadpool;// 线程池
    const int m_runModel;
    int m_fileNum;
    bool m_force_copy_start;
    
};


#endif //_PS_PROXY_H_
