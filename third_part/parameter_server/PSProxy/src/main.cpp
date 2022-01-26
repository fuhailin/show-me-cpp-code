/*
 * @Company: TWL
 * @Author: gu shitao
 * @Email: gushitao@kanzhun.com
 * @Date: 2020-01-07 11:54:40
 */

#include "psProxy_module.h"
#include "psProxy.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/server/TThreadPoolServer.h>

#include <memory>
#include "assert_exit.h"
#include "port_holder.h"
#include "logger.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;
using json = nlohmann::json;
using std::shared_ptr;
using namespace  ::ps;

extern log4cxx::LoggerPtr gLogger;// log句柄
json gJsonConf;// 全局配置句柄
shared_ptr<psProxy> gPtrPsProxy;// psProxy
shared_ptr<tcmcp_psProxyServClient> gPtrTcmcpPsProxy;



int gRunModle = -1;// 启动模式，0-TRAINING, 1-SERVERING, 2-FOLLOW

string gTcmcpUrl;// servering模式时，连接的training集群zkUrl
string gTcmcpPath;// servering模式时，连接的training集群zkPath

string gTcmcpRegistePath;// 本次psProxy注册到tcmcp_psProxy的路径
int gThriftThreadNum = -1; //本次psProxy thrift服务的线程数
std::string gModelName;    //本次psProxy代理上ps运行的模型名，一般为真实模型名+(offine, online, readtime),如 training_offline
std::string gConfFile; // 本次psProxy需要的ps和zookeeper配置的路径信息
std::string gLogFile; // 本次psProxy需要的ps和zookeeper配置的路径信息
std::string gSelfZkPath;
std::string gSelfZkUrl;
int gGroupNum = -1;  // 本次psProxy需要的ps的 group数
int gThriftPort= -1; //本次psProxy需要的thrit服务端口
int gCustomFileNum= -1; //命令行指定启动cf数
bool force_copy_start = false;

std::shared_ptr<spdlog::logger> logger;
const std::string loggerName = "ps_proxy_logger";

void initLogger(const std::string& loggerName, const std::string& logFileName) {
    spdlog::set_level(spdlog::level::info);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%f] [thread %t] [%n] [%l] %v");
    // add a thread to flush log, use in multi-thread mode
    spdlog::flush_every(std::chrono::seconds(1)); // flush every 1s
    // add a log thread
    logger = spdlog::daily_logger_mt<spdlog::async_factory>(loggerName, logFileName, 0, 0);
}


int createTcmcpPsProxy(std::string sync_zk_url,std::string sync_zk_path_incl_model_name) {
    // 建立tcmcp_psProxy链接
    if (sync_zk_url == "") {
        gTcmcpUrl = gJsonConf["zookeeper"]["zk_url"];
    } else {
        gTcmcpUrl = sync_zk_url;
    }

    std::string tmp = "/"+gModelName+"_offline";
    if (sync_zk_path_incl_model_name == "") {
        gTcmcpPath = gJsonConf["zookeeper"]["registe"]["zk_path"];
        gTcmcpPath = gTcmcpPath+tmp;
    } else {
        gTcmcpPath = sync_zk_path_incl_model_name;
    }

    gPtrTcmcpPsProxy.reset(new tcmcp_psProxyServClient(gTcmcpUrl, gTcmcpPath, 2, 1000*60*120/*数据迁移可能需要很长时间*/));
    int ret = gPtrTcmcpPsProxy->init();
    if(ret)
    {
        char msg[128] = {0};
        snprintf(msg, sizeof(msg), " gPtrTcmcpPsProxy->init()=%d", ret);
        logger->error("{tcmcpPsProxy init failed {}", msg);
        return -1;
    }
    logger->info( "TcmcpPsProxy created");
    return 0;
}

void resetTcmcpPsProxy() {
    gPtrTcmcpPsProxy.reset();
}

class psProxyServHandler : virtual public psProxyServIf
{
public:
    psProxyServHandler(){}

public:
    void push(const std::map<Key, std::string> & key_vals)
    {
        logger->info("psProxyServHandler::push start, key_vals.size(): {}", key_vals.size());
        int ret = gPtrPsProxy->push(key_vals);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "push failed, return [%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::push end");
    }

    void sync_push(const std::map<Key, std::string> & key_vals)
    {
        logger->info("psProxyServHandler::sync_push start, key_vals.size(): {}", key_vals.size());
        int ret = gPtrPsProxy->sync_push(key_vals);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "sync_push failed, return [%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::sync_push end");
    }

    void pushemb(const std::map<Key, std::string> & key_vals)
    {
        logger->info("psProxyServHandler::pushemb start, key_vals.size(): {}", key_vals.size());
        int ret = gPtrPsProxy->pushemb(key_vals);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "pushemb failed, return [%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::pushemb end");
    }

    void pushada(const std::map<Key, std::string> & key_vals)
    {
        logger->info("psProxyServHandler::pushada start, key_vals.size(): {}", key_vals.size());
        int ret = gPtrPsProxy->pushada(key_vals);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "pushada failed, return [%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::pushada end");
    }

    void pull(std::map<Key, std::string> & _return, const std::set<Key> & keys)
    {
        logger->info("psProxyServHandler::pull start, keys.size(): {}", keys.size());
        int ret = gPtrPsProxy->pull(_return, keys);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "pull failed, return [%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::pull end");
    }

    void pull_online(std::map<Key, std::string> & _return, const std::set<Key> & keys)
    {
        logger->info("psProxyServHandler::pull_online start, keys.size(): {}", keys.size());
        int ret = gPtrPsProxy->pull_online(_return, keys);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "pull_online failed, return [%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::pull_online end");
    }

    void pull_online2(std::map<ps::Key, std::string> & _return, const std::vector<Key> & keys) {
        logger->info("psProxyServHandler::pull_online2 start, keys.size(): {}", keys.size());
        std::set<Key> keys_set;
        for(auto& key:keys) {
            keys_set.insert(key);
        }
        int ret = gPtrPsProxy->pull_online(_return, keys_set);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "pull_online2 failed, return[%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::pull_online2 end, result num: {}", _return.size());
    }

    void replication(const std::string& zkUrl, const std::string& zkPath)
    {
        logger->info("psProxyServHandler::replication start, zkUrl: {}, zkPath: {}", zkUrl, zkPath);
        int ret = gPtrPsProxy->replication(zkUrl, zkPath);
        if(ret != 0)
        {
            char msg[1024] = {0};
            snprintf(msg, sizeof(msg), "replication failed, zkUrl=[%s], zkPath=[%s]", zkUrl.data(), zkPath.data());
            logger->error( "{}", msg);
        }
        else
        {
            logger->info( "replication OK");
        }
        logger->info("psProxyServHandler::replication end");
    }

    void stop_replication(const std::string& zkUrl, const std::string& zkPath)
    {
        logger->info("psProxyServHandler::stop_replication start, zkUrl: {}, zkPath: {}", zkUrl, zkPath);
        int ret = gPtrPsProxy->stop_replication(zkUrl, zkPath);
        if(ret != 0)
        {
            char msg[1024] = {0};
            snprintf(msg, sizeof(msg), "replication failed, zkUrl=[%s], zkPath=[%s]", zkUrl.data(), zkPath.data());
            logger->error( "{}", msg);
        }
        else
        {
            logger->info( "stop replication OK");
        }
        logger->info("psProxyServHandler::stop_replication end");
    }

    void copy_data(const std::map<std::string, std::string> & col_num)
    {
        logger->info("psProxyServHandler::copy_data start");
        int ret = gPtrPsProxy->copy_data(col_num);
        if(ret != 0)
        {
            logger->error( "copy_data failed.");
        }
        else
        {
            logger->info( "copy_data OK");
        }
        logger->info("psProxyServHandler::copy_data end");
    }

    void heartbeat(std::string& _return, const int32_t input)
    {
        logger->info("psProxyServHandler::heartbeat start");
        int ret = gPtrPsProxy->heartbeat(_return, input);
        if(ret != 0)
        {
            logger->error( "heartbeat failed.");
        }
        else
        {
            logger->info( "heartbeat OK");
        }
        logger->info("psProxyServHandler::heartbeat end");
    }

    void backup(std::string& _return, const std::string& type, const std::string& backup_name) {
        logger->info("psProxyServHandler::backup start");
        int ret = gPtrPsProxy->backup(_return, type, backup_name);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "backup failed, return[%d]", ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::backup end");
    }

    void change_sync_to(std::string& _return, const std::string& zk_url, const std::string& zk_path) {

        int ret;
        ret = createTcmcpPsProxy(zk_url, zk_path);
        if (ret!=0) {
            _return = std::string("failed: createTcmcpPsProxy");
            return;
        }

        if (zk_url != ""){
            ret = gPtrPsProxy->replication(gSelfZkUrl, gSelfZkPath);
        } else {
            ret = gPtrPsProxy->stop_replication(gSelfZkUrl, gSelfZkPath);
        }
        resetTcmcpPsProxy();

        if (ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "backup failed, return[%d]", ret);
            logger->error( "{}", msg);
            _return = std::string("failed:") + std::string(msg);
            return;
        }
        _return = std::string("ok");
        return;
    }

    void status_cmd(std::string& _return, const std::string& cmd, const std::vector<std::string> & values) {
        logger->info("psProxyServHandler::status_cmd start");
        int ret = gPtrPsProxy->status_cmd(_return, cmd, values);
        if(ret != 0)
        {
            char msg[128] = {0};
            snprintf(msg, sizeof(msg), "status command %s failed, return[%d]", cmd.c_str(), ret);
            logger->error( "{}", msg);
        }
        logger->info("psProxyServHandler::status_cmd end");
    }
};


void handleInput(int argc, char **argv)
{
    std::string a(argv[1]);
        int j(1);
    while(j != argc){
        std::string a(argv[j]);
        j++;
        if(a == "-rm" || a == "-run_model"){

            // cout<<"haha"<<endl;
            if(!strncmp(argv[j], "training", strlen("training"))){
                gRunModle = TRAINING;
            }else if(!strncmp(argv[j], "servering", strlen("servering"))){
                gRunModle = SERVERING;
            }else if(!strncmp(argv[j], "follow", strlen("follow"))){
                gRunModle = FOLLOW;
            }else{
                printf("usage: \n");
                printf("    ./bazel-bin/psProxy -rm training\n");
                printf("    ./bazel-bin/psProxy -rm servering \n");
                printf("    ./bazel-bin/psProxy -rm follow\n");
                assert_exit(1);
            }
            j++;
        }

        if(a == "-thrift_thread_num"){
            std::string tmp(argv[j]);
            j++;
            gThriftThreadNum= std::stoi(tmp);
        }

        if(a=="-mn" || a == "-model_name"){
            std::string tmp(argv[j]);
            gModelName = tmp;
            j++;
        }

        if(a=="-conf"){
            std::string tmp(argv[j]);
            gConfFile = tmp;
            j++;
        }

        if(a=="-log"){
            std::string tmp(argv[j]);
            gLogFile = tmp;
            j++;
        }

        if(a == "-g" || a == "-group_num"){
            string tmp(argv[j]);
            gGroupNum = stoi(tmp);
            j++;
        }

        if(a == "-tp" || a == "-thrift_port"){
            std::string tmp(argv[j]);
            gThriftPort = stoi(tmp);
            j++;

        }

        if(a == "-cs" || a == "-copy_start"){
            //force to call copy_start
            force_copy_start = true;
        }

        if(a == "-cf"){
            //rocksdb cf count
            std::string tmp(argv[j]);
            gCustomFileNum = stoi(tmp);
        }
    }
}

/*
* 初始化配置文件
*/
void initConf()
{
    #define CONF_PATH_LOG4CXX     "conf/log4cxx.properties"
    #define CONF_PATH_CONF        "PSProxy/conf/conf.json"
    log4cxx::PropertyConfigurator::configure(gLogFile);
    logger->info("init {} ok ...", gLogFile);
    if(!gcommon::readConf2Json(gConfFile, gJsonConf))
    {
        logger->error("readConf2Json error:[{}]...exit!", gLogFile);
        assert_exit(1);
    }
    logger->info("initConf ok...");
}

/*
* 初始全局资源
*/
void initGlobalResource()
{
    std::string runMode = "training";
    if (gRunModle == SERVERING) {
        runMode = "serving";
    }

    // 读取命令行参数，修改conf中的默认配置
    int master_num= gJsonConf["psProxy"]["ps_proxy_info"]["master_num"].get<int>();
    if (gRunModle != SERVERING) {
        master_num = 20;
    }

     std::string zk_path = gJsonConf["psProxy"]["ps_proxy_info"]["zk_path"];
     if(gModelName.empty()){
        logger->error("You must input the model name\n");
        assert_exit(1);
     }else{
         if(gRunModle == TRAINING){
            zk_path = zk_path+"/"+gModelName+"_offline";
         }else if(gRunModle == SERVERING){

            zk_path = zk_path+"/"+gModelName+"_online";
         }else{
            logger->error("gRunModle is invalid!!!\n");
            return;
         }
     }

    gSelfZkPath = zk_path;
    gSelfZkUrl = gJsonConf["psProxy"]["ps_proxy_info"]["zk_url"];
    // 初始化psProxy
    logger->info("run_mode: {}, master_num: {}", runMode, master_num);
    gPtrPsProxy.reset(new psProxy(
                            gJsonConf["psProxy"]["ps_proxy_info"]["zk_url"],
                            zk_path,
                            gJsonConf["psProxy"]["ps_proxy_info"]["pool_size"].get<int>(),
                            master_num,
                            gJsonConf["psProxy"]["ps_proxy_info"]["check_on_line"].get<int>() == 0 ? false : true,
                            force_copy_start,
                            gJsonConf["psProxy"]["ps_proxy_info"]["timeout"].get<int>(),
                            gJsonConf["psProxy"]["ps_proxy_info"]["success_rate"].get<int>(),
                            gJsonConf["psProxy"]["ps_proxy_info"]["switchover_check_times"].get<int>(),
                            gRunModle
    ));
    int ret = gPtrPsProxy->init();

    if(ret != gGroupNum)
    {
        char msg[128] = {0};
        snprintf(msg, sizeof(msg), "gPtrPsProxy->init()=%d, group_number=%d...", ret, gGroupNum);
        logger->error("{}", msg);
        assert_exit(1);
    }
    else
    {
        logger->info("psProxy init OK");
        char msg[1024]={0};
        snprintf(msg, sizeof(msg),  "\npsProxy info:\n"
                                    "group_num=[%d]\n"
                                    "zk_url=[%s]\n"
                                    "zk_path=[%s]\n"
                                    "pool_size=[%d]\n"
                                    "master_num=[%d]\n"
                                    "check_on_line=[%s]\n"
                                    "timeout=[%d]\n"
                                    "success_rate=[%d%%]\n"
                                    "switchover_check_times=[%d]\n"
                                    "modle=[%d]",
                                    ret,
                                    string(gJsonConf["psProxy"]["ps_proxy_info"]["zk_url"]).data(),
                                    string(gJsonConf["psProxy"]["ps_proxy_info"]["zk_path"]).data(),
                                    gJsonConf["psProxy"]["ps_proxy_info"]["pool_size"].get<int>(),
                                    gJsonConf["psProxy"]["ps_proxy_info"]["master_num"].get<int>(),
                                    gJsonConf["psProxy"]["ps_proxy_info"]["check_on_line"].get<int>() == 0 ? "false" : "true",
                                    gJsonConf["psProxy"]["ps_proxy_info"]["timeout"].get<int>(),
                                    gJsonConf["psProxy"]["ps_proxy_info"]["success_rate"].get<int>(),
                                    gJsonConf["psProxy"]["ps_proxy_info"]["switchover_check_times"].get<int>(),
                                    gRunModle
                                    );
        logger->info("{}", msg);
    }


    if(gRunModle == SERVERING)
    {
        // 初始化后删除
        gPtrTcmcpPsProxy.reset();
    }

    logger->info("initGlobalResource ok..." );
}

void TestCreateHandler(ZKErrorCode errcode, const std::string& path, const std::string& value, void* context) {
	if (errcode == kZKSucceed) {
        logger->info("TestCreateHandler-[kZKSucceed] path={}, value={}", path, value);
	} else if (errcode == kZKError) {
        logger->error("TestCreateHandler-[kZKError] path={} ", path);
	} else if (errcode == kZKNotExist) {
        logger->error("TestCreateHandler-[kZKNotExist] path={} ", path);
	} else if (errcode == kZKExisted) {
        logger->error("TestCreateHandler-[kZKExisted] path={} ", path);
	}
    logger->info("exit the handler");
}

static std::string zkRegPath;

void TestCreateHandler1(ZKErrorCode errcode, const std::string& path, const std::string& value, void* context) {
	if (errcode == kZKSucceed) {
        logger->info("TestCreateHandler-[kZKSucceed] path={}, value={}", path, value);
        zkRegPath = path;
	} else if (errcode == kZKError) {
        logger->error("TestCreateHandler-[kZKError] path={} ", path);
	} else if (errcode == kZKNotExist) {
        logger->error("TestCreateHandler-[kZKNotExist] path={} ", path);
	} else if (errcode == kZKExisted) {
        logger->error("TestCreateHandler-[kZKExisted] path={} ", path);
	}
    logger->info("exit the handler");
}

void registeIntoTcmcpZK()
{
    ZKClient& zkclient = ZKClient::GetInstance();
    int timeout = gJsonConf["zookeeper"]["timeout"];
    if (!zkclient.Init(gJsonConf["zookeeper"]["zk_url"], timeout))
    {
        logger->error("ZKClient failed to init...");
        assert_exit(1);
    }

    gJsonConf["zookeeper"]["registe"]["info"]["ip"] = gcommon::getIp();// 赋值本地ip
    gJsonConf["zookeeper"]["registe"]["info"]["port"] = gThriftPort;// 对外的thrift port

    string zk_path = gJsonConf["zookeeper"]["registe"]["zk_path"];
    // std::cout<<gJsonConf["zookeeper"]["registe"]["info"].dump()<<std::endl;

    bool succeed;
    //zk_path+="psProxy";
    if(gModelName.empty()){
        logger->error("You must input the model name\n");
        assert_exit(1);
    }else{
        if(gRunModle == TRAINING){
            zk_path = zk_path+"/"+gModelName+"_offline";
        }else if(gRunModle == SERVERING){
            zk_path = zk_path+"/"+gModelName+"_online";
        }else{
            logger->error("gRunModle is invalid!!!\n");
            return;
        }
    }
    //zk_path = zk_path+"/"+gModelName;
    succeed = zkclient.Create(zk_path, zk_path, ZOO_PERSISTENT, TestCreateHandler, NULL);
    if (!succeed) {
        logger->error("{} failed to Create ", zk_path);
        return;
    } else {
        logger->info("{} success create!!", zk_path);
    }
    gTcmcpRegistePath = zk_path
                        +"/"+gJsonConf["zookeeper"]["registe"]["info"]["ip"].get<string>()
                    +":"+to_string(gJsonConf["zookeeper"]["registe"]["info"]["port"]);

    succeed =   zkclient.Create(gTcmcpRegistePath,
                                    gJsonConf["zookeeper"]["registe"]["info"].dump(),
                                    ZOO_EPHEMERAL,TestCreateHandler1, NULL );
    gTcmcpRegistePath = zk_path;
    if (!succeed) {
        logger->error("{} failed to Create ", zk_path);
        return;
    } else {
        logger->info("{} success create!!", zk_path);
    }

    logger->info("registeZK ok...");
}

static void unregisterFromZK(int signal) {
    if (zkRegPath=="") {
        logger->info("on signal {}, {} is not registered", signal, zkRegPath);
        return;
    }
    ZKClient &zkclient = ZKClient::GetInstance();
    zkclient.Delete(zkRegPath);
    logger->info("on signal {}, {} is deleted from zk", signal, zkRegPath);
    exit(signal);
}

static void resetSigHandlers() {
    signal(SIGKILL, unregisterFromZK);
    signal(SIGTERM, unregisterFromZK);
    signal(SIGHUP,  unregisterFromZK);
    signal(SIGSTOP, unregisterFromZK);
    signal(SIGTSTP, unregisterFromZK);
    signal(SIGINT,  unregisterFromZK);
}

void initLog(){
    std::string logFileName = "/data/logs/ps_logs/";
    logFileName += gModelName +"_proxy.log";
    initLogger(loggerName, logFileName);
    logger->info("ps proxy starting, loggerName: {}, logFileName: {}", loggerName, logFileName);
}

void serverRun()
{
    int thread_num = gJsonConf["psProxy"]["thrift_thread_number"].get<int>();
    if(gThriftThreadNum != -1){
        thread_num = gThriftThreadNum;
    }
    ::apache::thrift::stdcxx::shared_ptr<psProxyServHandler> handler(new psProxyServHandler());
    ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new psProxyServProcessor(handler));
    shared_ptr<TNonblockingServerTransport> serverTransport(new TNonblockingServerSocket(gThriftPort));
    ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(thread_num);
    shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory > (new PosixThreadFactory());
    threadManager->threadFactory(threadFactory);
    threadManager->start();

    TNonblockingServer server(processor, protocolFactory, serverTransport, threadManager);//using pool of thread

    logger->info("server run...");
    server.serve();
}


void resourceHolder(int& fd) {
    int port;
    if (gThriftPort == 0) {
        getHoldRandomPort(fd, port);
        gThriftPort = port;
    }
    else {
        fd = holdPort(gThriftPort);
        if(fd < 0) {
            std::cout << "thrift port is used" << std::endl;
            std::cerr << "thrift port is used" << std::endl;
            exit(5);
        }
    }
}

void resourceHolderRelease(int fd) {
    close(fd);
}

int main(int argc, char **argv)
{
    // 处理输入参数
    handleInput(argc, argv);

    int thrift_port_holder_fd;
    resourceHolder(thrift_port_holder_fd);

    // 初始化日志
    initLog();

    // 读取配置
    initConf();
    // 初始化全局资源
    initGlobalResource();
    // 注册zk信息
    resetSigHandlers();
    registeIntoTcmcpZK();

    resourceHolderRelease(thrift_port_holder_fd);
    // 服务启动
    serverRun();

    return 0;
}

/*

training ps01

servering v-ps-09
/group6_test/gust/ps_20200110
*/

