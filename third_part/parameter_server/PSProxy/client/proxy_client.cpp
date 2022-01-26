
#include <vector>
#include <string>
#include <atomic>
#include <cstdlib>
#include <thread>
#include <algorithm>

#include "tcmcp_psProxyServ.h"
#include "city.h"

// 测试环境：开发机  172.20.6.222
#define ZK_PATH "/psProxy/tcmcp/base_ctr_0111_offline"
#define ZK_URL "172.20.6.222:2181,172.20.6.222:2182,172.20.6.222:2183"

#define THREAD_NUMBER 1
#define CONNECT_NUMBER 5

std::atomic< int >  g_total(0);

bool g_run = true;
void sig_handler(int signo)
{
  if (signo == SIGINT)
    g_run = false;
}

void pushData(shared_ptr<tcmcp_psProxyServClient> p, double mytimes, int rc_ok, int i )
{

    std::map<Key, std::string>  key_vals;

    for(int i = 0 ; i < 10000;++i)
        key_vals[i] = to_string(i*100)+"gust";
    p->tcmcp_push(key_vals);

    printf("  pushData    over ...\n");
    sleep(1);
}

void pullData(shared_ptr<tcmcp_psProxyServClient> p, double mytimes, int rc_ok, int i )
{

    std::map<Key, std::string>  key_vals;
    std::set<Key>  keys;
    for(int i = 0 ; i < 10000;++i)
        keys.insert(get_fid(to_string(i), 5));
    printf("%d aaaaaa\n",  p->tcmcp_pull(key_vals, keys));

    printf("   pullData   over ...\n");
}

void WorkerThread(shared_ptr<tcmcp_psProxyServClient> p, double mytimes, int rc_ok, int i )
{


    int rc = -1;

    while(g_run)
    {
        string ret;
        int t = g_total++;
        rc = p->tcmcp_heartbeat(ret, t);
        printf("  tcmcp_heartbeat ok ---- ");

        if(rc == rc_ok && ret == to_string(t))
        {

            printf("  [success][%d] tcmcp_heartbeat %d times\n", rc,t);
            /*
            for(auto& r : pullret)
                printf("  %ld, %s\n", r.first, r.second.data());
            */
        }
        else
        {
            printf("  [failed] tcmcp_heartbeat return[%d]  input[%d],return[%s]  \n", rc, t, ret.data());
        }



        if(g_run)
            usleep(int(1000 * 1000 / mytimes));
    }

    printf("   %d    over ...\n", i);
}


int main(int argc, char **argv)
{
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGINT\n");

    double mytimes = 10.0;
    if(argc == 2)
    {
        mytimes = atof(argv[1]);
    }

    {
        shared_ptr<tcmcp_psProxyServClient> p(new tcmcp_psProxyServClient(
                                                    ZK_URL,
                                                    ZK_PATH,
                                                    CONNECT_NUMBER,
                                                    10000));

        int num = p->init();
        if(num)
        {
            printf("  tcmcp_psProxyServClient.init(); = %d \n", num);
            return 1;
        }

        vector<thread> threadList;
        for(int i = 0; i < THREAD_NUMBER; i++)
        {
            threadList.emplace_back(thread(WorkerThread, p, mytimes, 0, i));
        }
        std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));

    }


    printf("hello world ....\n");
    return 0;
}



// int main1(int argc, char **argv)
// {
//     if (signal(SIGINT, sig_handler) == SIG_ERR)
//         printf("\ncan't catch SIGINT\n");

//     double mytimes = 10.0;
//     if(argc == 2)
//     {
//         mytimes = atof(argv[1]);
//     }


//     {
//         shared_ptr<psProxy> p (new psProxy(ZK_URL, ZK_PATH, 5));
//         int num = p->init();
//         if(num < 1)
//         {
//             printf("  ps_proxy.init(); = %d \n", num);
//             return 1;
//         }
//         int rc_ok = static_cast<int>(pow(10,num));
//         usleep(1000 * 300);

//         int cnt = 0;
//         while(g_run)
//         {
//             int rc = -1;


//             map<Key, string> pullret;
//             set<Key> keys;
//             for(int i = 0; i < 5 ; ++i)
//             {
//                 keys.insert(get_fid(to_string(i+3) + "abcd", (int64_t(i%2))));
//             }
//             rc = p->pull(pullret, keys);
//             ++cnt;
//             if(rc == rc_ok)
//             {

//                 printf("  [success][%d] pull %d times\n", rc,cnt);
//                 /*
//                 for(auto& r : pullret)
//                     printf("  %ld, %s\n", r.first, r.second.data());
//                 */
//             }
//             else
//             {
//                 printf("  [failed][%d] pull  %d \n", rc, cnt);
//             }


//             string ret;
//             rc = p->heartbeat(ret, cnt);
//             if(rc == 0)
//             {
//                 printf("  [success][%d] proxy_heartbeat=%s [%d]\n", rc, ret.data(), cnt);
//             }
//             else
//             {
//                 printf("  [failed][%d] proxy_heartbeat  %d \n", rc, cnt);
//             }
//             ++cnt;


//             if(g_run)
//                 usleep(int(1000 * 1000 / mytimes));
//         }
//     }


//     printf("hello world ....\n");
//     return 0;
// }

 /*

vi ~/.bashrc
source ~/.bashrc

./gust/myLearn/parameter_server/bazel-bin/proxy/proxy  10

alias gm1='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 1000 -thread_num 3  -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9011 -mp 9001'
alias gs11='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 1000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9012 -mp 9002 -sl 172.16.23.16:9001'
alias gs12='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 1000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9011 -mp 9001-sl 172.16.23.16:9002'
alias gm2='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 2000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9021 -mp 9003'
alias gs21='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 2000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9022 -mp 9004  -sl 172.16.23.16:9003'
alias gs22='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 2000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9021 -mp 9003 -sl 172.16.23.16:9004'
alias gm3='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 3000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9031 -mp 9005'
alias gs31='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 3000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9032 -mp 9006 -sl 172.16.23.16:9005'
alias gs32='./gust/myLearn/parameter_server/bazel-bin/psthrift/serverRegisted -g 3000 -thread_num 3   -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9031 -mp 9005 -sl 172.16.23.16:9006'



./gust/myLearn/parameter_server/psthrift/bazel-bin/serverRegisted -g 1000 -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9011 -mp 9001
./gust/myLearn/parameter_server/psthrift/bazel-bin/serverRegisted -g 1000 -n ./gust/myLearn/parameter_server/psthrift/conf/recall.net -d ./gust/myLearn/parameter_server/psthrift/conf/db.conf -m ./gust/myLearn/parameter_server/psthrift/conf/recall.meta -mn proxy_test -tp 9012 -mp 9002 -sl 172.16.23.16:9001


create /namespace_gustTest/rocksdbProxy_test/version_1/1000/2 {"ip":"172.18.3.253","port":9999}

Alt+Shift 竖列选择 列编辑


测试用例（单线程已经全部验证）：
~主ok，备ok
~主ok，备挂，补充备成功
~主ok，备挂，补充备失败、补充备成功
~主ok，备无，补充备成功
~主ok，备无，补充备失败，补充备成功
~主ok，备无，主挂，补充主成功，补充备成功
~主ok，备无，主挂，补充主失败、补充主成功，补充备成功

~主挂、备升主成功
~主挂、备升主成功、补充备成功
~主挂、备升主成功、补充备失败
~主挂、备升主成功、补充备失败、补充备成功

~主挂，备升主失败，补充主成功
~主挂，备升主失败，补充主失败，补充主成功


*/


/*

测试逻辑宏

;;;;;;;;;;;;;;\
static int i = 0 ; int ret = i % 50;\
if(ret == 7)\
{\
    i = i > 100 ? 0 : i+1;\
    *status = CONNECT_OFFLINE;\
    __OBJ__.deleteConnect(__INDEX__, p2connect->connectNodeKey);\
    __OBJ__.gProxy_Failed(__INDEX__);\
    cond->notify_one();\
    delete &__INDEX__;\
    return PROXY_CONNECT_OFFLINE;\
}\
i = i > 100 ? 0 : i+1;\
;;;;;;;;;;;;;;\

/algorithm_research_center/group6/gProxy/psProxy/

/algorithm_research_center/group6/tcmcp/psProxy/


*/

/*

????  psProxy对外服务的线程数为3时，第四个卡住了， 待确认


*/