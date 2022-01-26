#include "gProxy.h"
#include "psProxy.h"
#include "logger.h"

template<>
void PushFunc<Push>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals) {
    p2connect->client->push(key_vals);
}

template<>
void PushFunc<SyncPush>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals) {
    p2connect->client->sync_push(key_vals);
}

template<>
void PushFunc<PushEmb>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals) {
    p2connect->client->pushemb(key_vals);
}

template<>
void PushFunc<PushAda>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, std::string> & key_vals) {
    p2connect->client->pushada(key_vals);
}

template<>
void PullFunc<Pull>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, string> & _return, set<Key> & keys) {
    p2connect->client->pull(_return, keys);
}

template<>
void PullFunc<PullOnline>(stConnectNode<ps::ParaServClient> *p2connect, map<Key, string> & _return, set<Key> & keys) {
    p2connect->client->pull_online(_return, keys);
}

template<>
void StartFunc<Start>(stConnectNode<ps::ParaServClient> *p2connect, vector<int>& col_num, const int file_num) {
    p2connect->client->start(col_num, file_num);
}

template<>
void StartFunc<CopyStart>(stConnectNode<ps::ParaServClient> *p2connect, vector<int>& col_num, const int file_num) {
    p2connect->client->copy_start(col_num, file_num);
}

template<>
void SyncFunc<StartSync>(stConnectNode<ps::ParaServClient> *p2connect, string& zkUrl, string& zkPath) {
    p2connect->client->start_sync_client(zkUrl, zkPath);
}

template<>
void SyncFunc<StopSync>(stConnectNode<ps::ParaServClient> *p2connect, string& zkUrl, string& zkPath) {
    p2connect->client->stop_sync_client(zkUrl, zkPath);
}

template<>
void GetConnect<PullOnline>(psProxy& obj,bool & master){
    obj.serial++;
    if (obj.serial % 2 == 0) {
        master=false;
    }
}

template<>
void GetConnect<Pull>(psProxy& obj,bool & master){}

template<>
void PsPushFunc<Push>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals){
    res.push_back(obj.post_task(&psProxy::thread_push, obj, index, key_vals));
}

template<>
void PsPushFunc<SyncPush>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals){
    res.push_back(obj.post_task(&psProxy::thread_sync_push, obj, index, key_vals));
}

template<>
void PsPushFunc<PushEmb>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals){
    res.push_back(obj.post_task(&psProxy::thread_pushemb, obj, index, key_vals));
}

template<>
void PsPushFunc<PushAda>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & key_vals){
    res.push_back(obj.post_task(&psProxy::thread_pushada, obj, index, key_vals));
}

template<>
void PsPullFunc<Pull>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & ret, set<Key> & splitKey){
    res.push_back(obj.post_task(&psProxy::thread_pull, obj, index, ret, splitKey));
}

template<>
void PsPullFunc<PullOnline>(vector<future<int>> &res, psProxy& obj, int& index, map<Key, std::string> & ret, set<Key> & splitKey){
    res.push_back(obj.post_task(&(psProxy::thread_pull_online), obj, index, ret, splitKey));
}

template <typename Client>
int gproxy_heartbeat(psProxy& obj, int &index, string& ret, int input){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;

    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    p2connect->client->heartbeat(ret, input);
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template <typename Client, typename FuncTag>
int gproxy_push(psProxy& obj, int &index, map<Key, std::string> & key_vals){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;

    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    logger->info("before PushFunc<FuncTag>(p2connect, key_vals);");
                    PushFunc<FuncTag>(p2connect, key_vals);
                    logger->info("after PushFunc<FuncTag>(p2connect, key_vals);");
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            logger->error("in delete_conn");
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template <typename Client, typename FuncTag>
int gproxy_pull(psProxy& obj, int &index, map<Key, string> & _return, set<Key> & keys){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;
    GetConnect<FuncTag>(obj, master);
    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    PullFunc<FuncTag>(p2connect, _return, keys);
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template <typename Client, typename FuncTag>
int gproxy_start(psProxy& obj, int &index, vector<int>& col_num, const int file_num){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;

    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    int tmp = file_num;
                    StartFunc<FuncTag>(p2connect, col_num, tmp);
                   // p2connect->client->start(col_num, file_num);
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template <typename Client>
int gproxy_transport(psProxy& obj, int &index, map<string, string> & col_num){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;

    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    p2connect->client->transport(col_num);
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template <typename Client, typename FuncTag>
int gproxy_sync_client(psProxy& obj, int &index, string& zkUrl, string& zkPath){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;

    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    SyncFunc<FuncTag>(p2connect, zkUrl, zkPath);
                   // p2connect->client->start_sync_client(zkUrl, zkPath);
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template <typename Client>
int gproxy_status_cmd(psProxy& obj, int &index, string& reurn, string& cmd, std::vector<std::string> &values){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;

    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    p2connect->client->status_cmd(reurn, cmd, values);
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template <typename Client>
int gproxy_backup(psProxy& obj, int &index, std::string &ret, const std::string &type,
    const std::string &backup_name, map<string, string> & fileNum_ip){
    int rc = -1;
    bool master=true;
    stConnectNode<Client>* p2connect = nullptr;

    p2connect = obj.getConnect(index, master);

    if(p2connect == nullptr)
    {
        logger->info("--no connect");
        if(master==true)
            obj.gProxy_Failed(index);
        rc = PROXY_NO_CONNECT;
    }else{
        std::shared_ptr<std::mutex> mtx = p2connect->connectMutex;
        std::shared_ptr<std::condition_variable> cond = p2connect->connectCondition;
        std::shared_ptr<int> status = p2connect->status;
        bool delete_conn=false;
        {
            std::unique_lock<std::mutex> u(*mtx);
            cond->wait(u, [status](){return *status != GPROXY_CONNECT_USING;});
            try
            {
                if(*status == GPROXY_CONNECT_OK)
                {
                    *status = GPROXY_CONNECT_USING;
                    p2connect->client->backup(ret, type, backup_name, fileNum_ip);
                    *status = GPROXY_CONNECT_OK;
                    if(master==true)
                        obj.gProxy_Succ(index);
                    cond->notify_one();
                    rc = PROXY_SUCCESS;
                }
                else
                {
                    logger->error("--proxy conn not ok");
                    cond->notify_one();
                    rc = PROXY_CONNECT_OFFLINE;
                }
            }
            catch(apache::thrift::transport::TTransportException& e)
            {
                logger->error("--thrift::transport exception: {}", e.what());
                *status = GPROXY_CONNECT_OFFLINE;
                delete_conn=true;
                if(master==true)
                    obj.gProxy_Failed(index);
                cond->notify_one();
                if(!strncmp(e.what(), "No more data to read.", strlen("No more data to read.")))
                    rc = PROXY_CONNECT_OFFLINE;
                else
                    rc = PROXY_CONNECT_ERROR;
            }
            catch(std::exception& e)
            {
                logger->error("--exception: {}", e.what());
                *status = GPROXY_CONNECT_OK;
                cond->notify_one();
                if(strstr(e.what(), "failed: unknown result"))
                    rc = PROXY_INPUT_ERROR;
                else
                    rc = PROXY_UNKNOWN;
            }
        }

        if(delete_conn) {
            obj.deleteConnect(index, p2connect->connectNodeKey, master);
        }
    }
    delete &index;
    return rc;
}

template<typename FuncTag>
int ps_proxy_push(psProxy& obj, const map<Key, std::string> & key_vals){
    vector<map<Key, std::string>> vecSpliteKeysVals;
    obj.splite_keys_vals(vecSpliteKeysVals ,key_vals);
    vector<future<int>> res;
    int count_num = 0;
    for (int index = 0 ; index < static_cast<int>(vecSpliteKeysVals.size()); ++index)
    {
        int* p = new int(index);
        if(vecSpliteKeysVals[index].size()==0){
            delete p;
            ++count_num;
        }else{
            PsPushFunc<FuncTag>(res, obj, *p, vecSpliteKeysVals[index]);
        }
    }
    bool ret_ok = true;
    for (auto& s:res)
    {
        if (s.get()!=0){
            ret_ok = false;
            break;
        }
    }
    if (!ret_ok)
        return -1;
    return 0;
}

template<typename FuncTag>
int ps_proxy_pull(psProxy& obj, map<Key, string>& _return, const set<Key>& keys){
    vector<set<Key>> vecSpliteKeys;
    obj.splite_keys(vecSpliteKeys ,keys);
    vector<map<Key, string>> all_return(obj.getGroupNumber());
    vector<future<int>> res;
    int count_num = 0;
    for (int index = 0 ; index < static_cast<int>(vecSpliteKeys.size()); ++index)
    {
        int* p = new int(index);
        if(vecSpliteKeys[index].size()==0){
            delete p;
            ++count_num;
        }else{
            PsPullFunc<FuncTag>(res, obj, *p, all_return[index], vecSpliteKeys[index]);
        }
    }
    bool ret_ok = true;
    for (auto& s:res)
    {
        if (s.get()!=0){
            ret_ok = false;
            break;
        }
    }
    if (!ret_ok)
        return -1;
    for (auto& s:all_return)
    {
        _return.insert(s.begin(), s.end());
    }
    return 0;
}

template int gproxy_heartbeat<ps::ParaServClient>(psProxy& obj, int &index, string& ret, int input);
template int gproxy_backup<ps::ParaServClient>(psProxy& obj, int &index, std::string &ret, const std::string &type,
     const std::string &backup_name, map<string, string> & fileNum_ip);
template int gproxy_transport<ps::ParaServClient>(psProxy& obj, int &index, map<string, string> & col_num);
template int gproxy_status_cmd<ps::ParaServClient>(psProxy& obj, int &index, string& reurn, string& cmd, std::vector<std::string> &values);

template int gproxy_push<ps::ParaServClient, SyncPush>(psProxy& obj, int &index, map<Key, std::string> & key_vals);
template int gproxy_push<ps::ParaServClient, Push>(psProxy& obj, int &index, map<Key, std::string> & key_vals);
template int gproxy_push<ps::ParaServClient, PushAda>(psProxy& obj, int &index, map<Key, std::string> & key_vals);
template int gproxy_push<ps::ParaServClient, PushEmb>(psProxy& obj, int &index, map<Key, std::string> & key_vals);
template int gproxy_pull<ps::ParaServClient, Pull>(psProxy& obj, int &index, map<Key, string> & _return, set<Key> & keys);
template int gproxy_pull<ps::ParaServClient, PullOnline>(psProxy& obj, int &index, map<Key, string> & _return, set<Key> & keys);
template int gproxy_start<ps::ParaServClient, Start>(psProxy& obj, int &index, vector<int>& col_num, const int file_num);
template int gproxy_start<ps::ParaServClient, CopyStart>(psProxy& obj, int &index, vector<int>& col_num, const int file_num);
template int gproxy_sync_client<ps::ParaServClient, StartSync>(psProxy& obj, int &index, string& zkUrl, string& zkPath);
template int gproxy_sync_client<ps::ParaServClient, StopSync>(psProxy& obj, int &index, string& zkUrl, string& zkPath);

template int ps_proxy_push<Push>(psProxy& obj, const map<Key, std::string> & key_vals);
template int ps_proxy_push<SyncPush>(psProxy& obj, const map<Key, std::string> & key_vals);
template int ps_proxy_push<PushAda>(psProxy& obj, const map<Key, std::string> & key_vals);
template int ps_proxy_push<PushEmb>(psProxy& obj, const map<Key, std::string> & key_vals);
template int ps_proxy_pull<Pull>(psProxy& obj, map<Key, string>& _return, const set<Key>& keys);
template int ps_proxy_pull<PullOnline>(psProxy& obj, map<Key, string>& _return, const set<Key>& keys);


