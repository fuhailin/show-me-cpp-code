/*
 * 用法：./send_cmd_to_ps localhost:2182 test_tf_12345 enable_update_times
 *       ./send_cmd_to_ps [zk]           [model_name]  [cmd]
 */
#include "tcmcp_psProxyServ.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string.h>

using namespace std;
int main(int argc, char** argv) {
    if (argc<3) {
        cout << "use: cmd {zk} {model_name} {cmd}\n";
        cout << " eg. ./send_cmd_to_ps localhost:2181 test_tf_12345 enable_update_times\n";
        return 0;
    }

    std::string zk(argv[1]);
    std::string mn(argv[2]);
    std::string cmd="enable_update_times";
    vector<string> cmd_args;
    if (argc>3)
        cmd = string(argv[3])
    for (int i=0;argc>4+i;i++)
        cmd_args.push_back(argv[4+i]);
    cout << "zk:" << zk << " mn:" << mn << endl;
    std::string path = "/psProxy/tcmcp/" + mn + "_online";
    std::shared_ptr<tcmcp_psProxyServClient> client(new tcmcp_psProxyServClient(zk, path, 1, 120 * 1000 * 1000));
    client->init();
    int ret;
    std::string return_val;
    ret = client->tcmcp_status_cmd(return_val, cmd , cmd_args);
    cout << "retv:" << ret << " return:" << return_val << endl;
}
