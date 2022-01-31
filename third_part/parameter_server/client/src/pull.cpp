/* test ps pull & push */

#include <stdlib.h>
#include <string.h>

#include <iostream>

#include "ps_util.h"
#include "tcmcp_psProxyServ.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc < 4) {
    cout << "use: cmd {zk} {model_name} {fid}\n";
    cout << " eg. ./client localhost:2181 test_tf_12345 587521474491657948\n";
    return 0;
  }

  std::string zk(argv[1]);
  std::string mn(argv[2]);
  std::string str_fid(argv[3]);

  std::string path = "/psProxy/tcmcp/" + mn + "_offline";
  std::shared_ptr<tcmcp_psProxyServClient> client(
      new tcmcp_psProxyServClient(zk, path, 1, 120 * 1000 * 1000));
  client->init();

  uint64_t fid = stoll(str_fid);
  std::set<int64_t> keys;
  keys.insert(fid);

  std::map<int64_t, string> m1;
  int ret = client->tcmcp_pull(m1, keys);
  std::cout << "retcode:" << ret << " size:" << m1.size() << std::endl;

  if (m1.size() > 0) {
    string output;
    // std::cout << "output is " << m1.begin()->second << std::endl;
    std::vector<float> result = str2vec(m1.begin()->second);
    for (size_t i = 0; i < result.size(); i++) {
      output += to_string(result[i]);
      if (i < result.size() - 1) output += ",";
    }
    cout << output << "\n";
  }
}
