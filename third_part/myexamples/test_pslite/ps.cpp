#include "ps/ps.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

using namespace std;
using namespace ps;

template <typename Val> struct KVServerDefaultHandle1 {
  void operator()(const KVMeta &req_meta, const KVPairs<Val> &req_data,
                  KVServer<Val> *server) {
    size_t n = req_data.keys.size();
    KVPairs<Val> res;
    if (req_meta.push) {
      // cout<< "push\n";
      CHECK_EQ(n, req_data.vals.size());
    } else {
      // cout<< "pull\n";
      res.keys = req_data.keys;
      res.vals.resize(n);
    }
    for (size_t i = 0; i < n; ++i) {
      Key key = req_data.keys[i];
      if (req_meta.push) {
        store[key] += req_data.vals[i];
      } else {
        res.vals[i] = store[key];
      }
    }
    server->Response(req_meta, res);
  }
  std::unordered_map<Key, Val> store;
};
void StartServer() {
  if (!IsServer())
    return;
  cout << "启动Server\n";
  auto server = new KVServer<float>(0);
  server->set_request_handle(KVServerDefaultHandle1<float>());
  RegisterExitCallback([server]() { delete server; });
}

void RunWorker() {
  if (!IsWorker())
    return;
  cout << "启动Worker rank = " << MyRank() << "\n";
  KVWorker<float> kv(0);

  // init
  int num = 10;
  std::vector<Key> keys(num);
  std::vector<float> vals(num);

  int rank = MyRank();
  srand(rank + 7);
  for (int i = 0; i < num; ++i) {
    keys[i] = i;
    vals[i] = i * 10;
  }

  // push
  int repeat = 1;
  std::vector<int> ts;
  for (int i = 0; i < repeat; ++i) {
    ts.push_back(kv.Push(keys, vals));
  }
  for (int t : ts)
    kv.Wait(t);

  // pull
  std::vector<float> rets;
  kv.Wait(kv.Pull(keys, &rets));
  for (size_t i = 0; i < rets.size(); i++) {
    cout << MyRank() << " rets[" << i << "]" << rets[i] << endl;
  }
  cout << "结束\n";
}

int main(int argc, char *argv[]) {
  // setup server nodes
  StartServer();
  // start system
  Start();
  // run worker nodes
  RunWorker();
  // stop system

  Finalize();
  return 0;
}