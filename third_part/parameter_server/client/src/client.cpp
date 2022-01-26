/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-11-11 20:22:26
 */
#include "tcmcp_psProxyServ.h"
#include "cityhash/src/city.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
    std::shared_ptr<tcmcp_psProxyServClient> client(new tcmcp_psProxyServClient("127.0.0.1:2183", "/psProxy/tcmcp/flash_training_1112_online", 1, 120 * 1000 * 1000));
    client->init();
	int ret;
    //std::string return_val;
    //std::cout << "ret " << client->tcmcp_backup(return_val, "scp", "1102") << std::endl;
    //std::cout << return_val << std::endl;
    //sleep(2);

    // if (argc<=1) {
    //    std::cout << "input argv[1]" << std::endl; 
    // }
    // long fid = atoi(argv[1]);
    // std::map<int64_t,string> m;
    // {
    //     string val("1.12345");
    //     m[fid] = val;
    // }
    // ret = client->tcmcp_pushemb(m);
    // std::cout << "retcode:" << ret << std::endl;
    
    // std::set<int64_t> keys;
    // keys.insert(fid);
    // std::map<long,string> m1;
    // ret = client->tcmcp_pull_online(m1,keys);
    // std::cout << "retcode:" << ret << " size:" << m1.size() << std::endl;
    // for (auto i=m1.begin();i!=m1.end();i++) {
	//     //std::cout << "v:" << std::string(i) << std::endl;
	//     std::cout << "v:" << std::string(i->second) << std::endl;
    // }

    std::string return_val;
    //ret = client->tcmcp_backup(return_val,"scp","202011101900");
    std::cout << "retcode:" << ret << std::endl;

    long fid=1;
    for(;fid<100;fid++){
        std::set<int64_t> keys;
        keys.insert(fid);
        std::map<long,string> m1;
        ret = client->tcmcp_pull_online(m1,keys);
        std::cout << "retcode:" << ret << " size:" << m1.size() << std::endl;
    }
}
