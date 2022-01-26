#include "psProxy.h"
#include "logger.h"

extern std::shared_ptr<tcmcp_psProxyServClient> gPtrTcmcpPsProxy;
extern json gJsonConf;// 全局配置句柄
extern string gTcmcpRegistePath;
extern log4cxx::LoggerPtr gLogger;// log句柄
extern int gCustomFileNum;


int psProxy::init() {
    // 创建线程池
    logger->info("psProxy::init init create pool");
    createThreadpool();

    int gProxyRet = gProxyInit();// 返回实际启动的group数
    logger->info("psProxy::init gProxyRet", gProxyRet);

    if (gProxyRet == 0)
        return gProxyRet;// 没有集群直接退出

    int runPsRet = runPsProxy();// 正常返回0

    return gProxyRet + runPsRet * 10000;
}

/*
* 构造函数
*/
psProxy::psProxy(const string zkHost,
                 const string zkPath,
                 const int poolSize,
                 const int masterNumber,
                 const bool checkOnline,
                 const bool force_copy_start,
                 const int psTimeout,
                 const int successRate,
                 const int switchoverCheckTimes,
                 const int runModel,
                 const int fileNum,
                 const int zkTimeout,
                 const double backgroundThreadCheckTimes
) :
        gProxy(zkHost, zkPath, masterNumber, psTimeout, successRate, switchoverCheckTimes, checkOnline,
               zkTimeout, backgroundThreadCheckTimes, fileNum),
        m_poolSize(poolSize),
        m_threadpool(nullptr),
        m_runModel(runModel),
        m_fileNum(fileNum),
        m_force_copy_start(force_copy_start) {
    if (gCustomFileNum > 0) {
        m_fileNum = gCustomFileNum;
    }
}

int psProxy::psProxyOK() {
    static int rc = 1;
    if (rc == 1) {
        rc = static_cast<int>(pow(10, getGroupNumber()));
    }

    return rc;
}


psProxy::~psProxy() {
}

/*
* 【主线程接口】【纯虚函数】创建链接节点并挂在连接池上
*/
void psProxy::createConnect(stConnectNode<ParaServClient>& connectNode, const string& ip, const int port) {
    shared_ptr<TSocket> socket(new TSocket(ip, port));
    socket->setRecvTimeout(m_psTimeout);
    shared_ptr<TTransport> transport(new TFramedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    try {
        transport->open();
    } catch (...) {
        logger->error("fail to connect ps server| {}:{}", ip, port);
        connectNode.client.reset();
        connectNode.transport.reset();
        throw "createConnect transport open error";
    }

    shared_ptr<ParaServClient> p(new ParaServClient(protocol));
    connectNode.client = p;
    connectNode.transport = transport;
}

int psProxy::heartbeat(string& ret, int input) {
    static int cnt = 0;
    int* index = new int(cnt % getGroupNumber());
    cnt++;
    cnt = cnt > 100000 ? 0 : cnt;
    return gproxy_heartbeat<ParaServClient>(*this, *index, ret, input);
}

void psProxy::createThreadpool() {
    m_threadpool = shared_ptr<boost::asio::thread_pool>(new boost::asio::thread_pool(m_poolSize));
}

int psProxy::pull(map<Key, string>& _return, const set<Key>& keys) {
    return ps_proxy_pull<Pull>(*this, _return, keys);
}

int psProxy::pull_online(map<Key, string>& _return, const set<Key>& keys) {
    return ps_proxy_pull<PullOnline>(*this, _return, keys);
}

int psProxy::push(const map<Key, std::string>& key_vals) {
    return ps_proxy_push<Push>(*this, key_vals);
}

int psProxy::sync_push(const map<Key, std::string>& key_vals) {
    return ps_proxy_push<SyncPush>(*this, key_vals);
}

int psProxy::pushemb(const map<Key, std::string>& key_vals) {
    return ps_proxy_push<PushEmb>(*this, key_vals);
}

int psProxy::pushada(const map<Key, std::string>& key_vals) {
    return ps_proxy_push<PushAda>(*this, key_vals);
}

int psProxy::thread_push(psProxy& obj, int& index, map<Key, std::string>& key_vals) {
    return gproxy_push<ParaServClient, Push>(obj, index, key_vals);
}

int psProxy::thread_sync_push(psProxy& obj, int& index, map<Key, std::string>& key_vals) {
    return gproxy_push<ParaServClient, SyncPush>(obj, index, key_vals);
}

int psProxy::thread_pushemb(psProxy& obj, int& index, map<Key, std::string>& key_vals) {
    return gproxy_push<ParaServClient, PushEmb>(obj, index, key_vals);
}

int psProxy::thread_pushada(psProxy& obj, int& index, map<Key, std::string>& key_vals) {
    return gproxy_push<ParaServClient, PushAda>(obj, index, key_vals);
}

int psProxy::thread_pull_online(psProxy& obj, int& index, map<Key, string>& _return, set<Key>& keys) {
    return gproxy_pull<ParaServClient, PullOnline>(obj, index, _return, keys);
}

int psProxy::thread_pull(psProxy& obj, int& index, map<Key, string>& _return, set<Key>& keys) {
    return gproxy_pull<ParaServClient, Pull>(obj, index, _return, keys);
}

void psProxy::splite_keys_vals(vector<map<Key, std::string>>& vecSpliteKeysVals,
                               const map<Key, std::string>& key_vals) {
    int group_num = getGroupNumber();
    vecSpliteKeysVals = vector<map<Key, std::string>>(group_num);
    for (auto& key_val:key_vals) {
        vecSpliteKeysVals.at(key_val.first % m_fileNum % group_num).insert(key_val);
    }
}

void psProxy::splite_keys(vector<set<Key>>& vecSpliteKeys, const set<Key>& keys) {
    int group_num = getGroupNumber();
    vecSpliteKeys = vector<set<Key>>(group_num);
    for (auto& key:keys) {
        vecSpliteKeys.at(key % m_fileNum % group_num).insert(key);
    }
}

// training模式启动
int psProxy::psStart(const int i, vector<int>& col_num) {
    int* index = new int(i);
    return gproxy_start<ParaServClient, Start>(*this, *index, col_num, m_fileNum);
}

int psProxy::thread_psStart(psProxy& obj, int& i, vector<int>& col_num, int& file_num) {
    int* index = new int(i);
    return gproxy_start<ParaServClient, Start>(obj, *index, col_num, file_num);
}

// servering模式启动
int psProxy::psCopyStart(const int i, vector<int>& col_num) {
    int* index = new int(i);
    return gproxy_start<ParaServClient, CopyStart>((*this), *index, col_num, m_fileNum);
}


int psProxy::runPsProxy() {
    logger->info("psProxy::runPsProxy() start");
    int ret = 0;

    // follow 模式直接返回
    if (m_runModel == FOLLOW)
        return ret;
    int groupNum = getGroupNumber();
    // 获得groupid和文件编号的对应关系
    map<int, vector<int>> hash;
    for (int i = 0; i < m_fileNum; ++i) {
        hash[i % groupNum].push_back(i);
    }
    logger->info("psProxy::runPsProxy m_fileNum: {}, hash.size: {}", m_fileNum, hash.size());

    // training 模式
    if (m_runModel == TRAINING || m_runModel == SERVERING) {
        std::vector<future<int>> res;
        std::vector<int> groups(groupNum);
        for (int i = 0; i < groupNum; ++i) {
            groups[i] = i;
            logger->info("start async: ");
            res.push_back(post_task(thread_psStart, *this, groups[i], hash[i], (int&) m_fileNum));
            logger->info("end start async: ");
        }
        for (unsigned i = 0; i < res.size(); i++) {
            auto retv = res[i].get();
            if (retv != 0) {
                logger->error("fail start group: {}", i);
            } else {
                logger->info("success start group: {}", i);
            }
            ret += retv;
        }
    }
    return ret;
}

int psProxy::copy_data(const map<string, string>& col_num) {
    logger->info("enter copy_data");
    vector<future<int>> res;
    logger->info("m_connectPool.size() = {}", m_connectPool.size());
    for (int index = 0; index < static_cast<int>(m_connectPool.size()); ++index) {
        int* p = new int(index);
        res.push_back(post_task(thread_transport, *this, *p, const_cast<map<string, string>&>(col_num)));
    }

    int ret = 1;
    for (auto& s:res) {
        ret = ret * 10 + s.get();
    }
    return ret;
}

int psProxy::thread_transport(psProxy& obj, int& index, map<string, string>& col_num) {
    return gproxy_transport<ParaServClient>(obj, index, col_num);
}


int psProxy::replication(const string& zkUrl, const string& zkPath) {
    vector<future<int>> res;
    for (int index = 0; index < static_cast<int>(m_connectPool.size()); ++index) {
        int* p = new int(index);
        res.push_back(
                post_task(thread_replication, *this, *p, const_cast<string&>(zkUrl), const_cast<string&>(zkPath)));
    }
    int ret = 1;
    for (auto& s:res) {
        ret = ret * 10 + s.get();
    }
    return ret;
}

int psProxy::stop_replication(const string& zkUrl, const string& zkPath) {
    vector<future<int>> res;
    for (int index = 0; index < static_cast<int>(m_connectPool.size()); ++index) {
        int* p = new int(index);
        res.push_back(
                post_task(thread_stop_replication, *this, *p, const_cast<string&>(zkUrl), const_cast<string&>(zkPath)));
    }
    int ret = 1;
    for (auto& s:res) {
        ret = ret * 10 + s.get();
    }
    return ret;
}

int psProxy::thread_replication(psProxy& obj, int& index, string& zkUrl, string& zkPath) {
    return gproxy_sync_client<ParaServClient, StartSync>(obj, index, zkUrl, zkPath);
}

int psProxy::thread_stop_replication(psProxy& obj, int& index, string& zkUrl, string& zkPath) {
    return gproxy_sync_client<ParaServClient, StopSync>(obj, index, zkUrl, zkPath);
}

string psProxy::checkout_start(int& group) {
    std::string _return;
    std::string cmd("checkout_start");
    std::vector<std::string> values;
    auto callcmd = [&]() {
        int* p = new int(group);
        return gproxy_status_cmd<ParaServClient>(*this, *p, _return, cmd, values);
    };
    callcmd();
    return _return;
}

string psProxy::get_start_status(int& group) {
    std::string _return;
    std::string cmd("get_status");
    std::vector<std::string> values;
    auto callcmd = [&]() {
        int* p = new int(group);
        return gproxy_status_cmd<ParaServClient>(*this, *p, _return, cmd, values);
    };
    callcmd();
    return _return;
}

string psProxy::checkout_start_token_otherwise_wait_started() {
    string start_type;
    int group_num = getGroupNumber();

    int first_group = 0;
    string result = checkout_start(first_group);

    string output = "group " + to_string(first_group) + " status is " + result;
    logger->info("{}", output);
    // cout << "group " << first_group << " status is " << result << endl;

    if (result == "STARTING_WITH_TOKEN") {
        //得到启动控制权，其他proxy无法再获得
        start_type = "STARTING_WITH_TOKEN";
        for (int i = first_group + 1; i < group_num; i++) {
            result = checkout_start(i);
            // cout << "group " << i << " status is " << result << endl;
        }
    } else if (result == "STARTING") {
        //等待正在启动的服务完成启动
        start_type = "STARTED";
        for (int i = first_group; i < group_num;) {
            result = get_start_status(i);
            // cout << "group " << i << " status is " << result << endl;
            if (result == "STARTED") {
                i++;
            } else {
                sleep(2);
            }
        }
    } else if (result == "STARTED") {
        //确认其他服务已完成启动
        start_type = "STARTED";
        for (int i = first_group + 1; i < group_num;) {
            result = get_start_status(i);
            // cout << "group " << i << " status is " << result << endl;
            if (result == "STARTED") {
                i++;
            } else {
                sleep(2);
            }
        }
    }
    return start_type;
}

int psProxy::set_all_started() {
    int group_num = getGroupNumber();
    for (int i = 0; i < group_num;) {
        std::string _return;
        std::string cmd("set_started");
        std::vector<std::string> values;
        auto callcmd = [&]() {
            int* p = new int(i);
            return gproxy_status_cmd<ParaServClient>(*this, *p, _return, cmd, values);
        };
        callcmd();
        if (_return == "OK")
            i++;
        else
            sleep(2);
    }
    return 0;
}

int psProxy::status_cmd(std::string& _return, const std::string& cmd, const std::vector<std::string>& values) {
    int sz = m_connectPool.size();
    vector<future<int> > res;
    vector<std::string> returns(sz);
    for (int index = 0; index < static_cast<int>(m_connectPool.size()); ++index) {
        int* p = new int(index);
        res.push_back(post_task(thread_status_cmd, *this, *p, returns[index], cmd, values));
    }
    _return = "OK";
    for (auto& s:res) {
        if (s.get() != 0) {
            _return = "failed";
        }
    }
    return 0;
}

int psProxy::backup(std::string& _return, const std::string& type, const std::string& backup_name) {
    int group_num = getGroupNumber();
    map<string, string> fileNum_ip;
    for (int i = 0; i < m_fileNum; ++i) {
        fileNum_ip[to_string(i)] = m_connectPool[i % group_num].master_ip;
    }

    vector<future<int>> res;
    vector<std::string> returns(group_num);
    for (int i = 0; i < static_cast<int>(m_connectPool.size()); ++i) {
        int* index = new int(i);
        res.push_back(post_task(thread_backup, *this, *index, returns[i], type, backup_name, fileNum_ip));
    }

    for (auto& s:res) {
        s.get();
    }

    _return = "OK";
    return 0;
}

int psProxy::thread_backup(psProxy& obj, int& index, std::string& ret, const std::string& type,
                           const std::string& backup_name, map<string, string>& fileNum_ip) {
    return gproxy_backup<ParaServClient>(obj, index, ret, type, backup_name, fileNum_ip);
}

int psProxy::thread_status_cmd(psProxy& obj, int& index, std::string& _return, const std::string& cmd,
                               const std::vector<std::string>& values) {
    GPROXY_NOT_POD(obj, ParaServClient, index, status_cmd, (_return, cmd, values));
}
