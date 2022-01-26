
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "ParaServ.h"
#include "city.h"
#include "para_serv_op.h"
#include "ps_util.h"
#include "time_function.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace std;
using namespace ps;

class TestServ {
 public:
  TestServ(){};
  TestServ(int port, std::string ip = "127.0.0.1");
  void test_push();
  void test_pushemb();
  void test_pushada();
  void test_pull();
  void test_pull_online();
  void test_start();
  void test_transport();
  void test_copy_start();
  void test_start_sync_client();
  void test_sync_del();
  void test_only_copy_start();
  void testSimplePush();

 private:
  std::shared_ptr<ParaServClient> client;
  std::set<int64_t> fids;
  std::map<int64_t, std::string> key_vals;
  int total_files;
  std::vector<int> col_index;
};

TestServ::TestServ(int port, std::string ip) {
  std::shared_ptr<TSocket> socket(new TSocket(ip, port));
  std::shared_ptr<TTransport> transport(
      new TFramedTransport(socket));  // for the noblockingserver
  std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  transport->open();

  client = std::make_shared<ParaServClient>(protocol);
}

void TestServ::test_start() {
  total_files = 2;
  for (int i(0); i < total_files; ++i) {
    col_index.push_back(i * 2);
  }
  client->start(col_index, total_files);
}

void TestServ::test_push() {
  std::set<int64_t> tmp_fids;
  tmp_fids.insert(get_fid("xuejian_ha", 5));
  client->pull(key_vals, tmp_fids);
  std::cout << *tmp_fids.begin() << std::endl;
  std::vector<float> value(str2vec(key_vals.begin()->second));
  Map<MatrixXf> emb(&value.at(0), 1, value.size());
  MatrixXf emb1(emb);
  MatrixXf ada(MatrixXf::Constant(1, value.size(), 0.1));
  MatrixXf grad(MatrixXf::Constant(1, value.size(), 0.1));
  ada += grad.cwiseAbs2();
  emb -=
      0.01 * grad.cwiseProduct((ada + MatrixXf::Constant(1, value.size(), 1E-6))
                                   .cwiseSqrt()
                                   .cwiseInverse());
  l2_norm_vec(emb, 0.7348469228349535);
  std::map<int64_t, std::string> client_key_val;
  client_key_val.insert(std::make_pair(*tmp_fids.begin(), vec2str(grad)));
  client->push(client_key_val);
  // sleep(10);
  client->pull(key_vals, tmp_fids);

  std::cout << emb << std::endl;
  std::vector<float> tmp2(str2vec(key_vals.begin()->second));
  Map<MatrixXf> emb2(&tmp2.at(0), 1, tmp2.size());

  std::cout << (emb2 - emb).cwiseAbs().sum() << std::endl;
  std::cout << (emb2 - emb1).cwiseAbs2().sum() << std::endl;
}

void TestServ::test_pushemb() {
  std::map<int64_t, std::string> tmp_kv;
  std::vector<std::string> keys(genRandStr(10, 1));
  std::set<int64_t> fidSet;
  int64_t test_fid;
  for (auto& key : keys) {
    test_fid = get_fid(key, 6);
    fidSet.insert(test_fid);
    tmp_kv.insert(std::make_pair(test_fid, "haha"));
  }
  client->pushemb(tmp_kv);
  std::map<int64_t, std::string> tmpp_kv;
  client->pull(tmpp_kv, fidSet);
  if (tmp_kv.at(test_fid) == tmpp_kv.at(test_fid)) {
    std::cout << "The push emb success!!!" << std::endl;
  }
}

void TestServ::test_pull() {
  std::vector<std::string> keys(genRandStr(10, 10000));
  for (auto& key : keys) {
    fids.insert(get_fid(key, 5));
  }
  int64_t test_fid = get_fid(keys.at(0), 5);
  client->pull(key_vals, fids);
  std::set<int64_t> tmp;
  tmp.insert(test_fid);
  std::map<int64_t, std::string> tmp_kv;
  client->pull(tmp_kv, tmp);
  if (tmp_kv.at(test_fid) == key_vals.at(test_fid)) {
    std::cout << "The pull success!!!" << std::endl;
  }
}

void TestServ::test_transport() {
  std::map<std::string, std::string> col_ip;
  for (auto& index : col_index) {
    col_ip.insert(std::make_pair(std::to_string(index), "172.21.34.88"));
  }
  client->transport(col_ip);
  std::cout << "transport success!!!" << std::endl;
}

void TestServ::test_copy_start() {
  std::map<int64_t, std::string> tmp_kv;
  // std::vector<int>& col_index;
  int total_files;
  {
    total_files = 5;
    for (int i(0); i < total_files; ++i) {
      col_index.push_back(i * 2);
    }
  }

  client->copy_start(col_index, total_files);
  // second_client->pull(tmp_kv, fids);
  // auto it = fids.begin();
  // int64_t test_fid = *it;
  // if (key_vals.at(test_fid) == tmp_kv.at(test_fid)) {
  //     std::cout<<"The transport and copy start success!!!!"<<std::endl;
  // }
}

void TestServ::test_only_copy_start() {
  std::shared_ptr<ParaServClient> second_client;
  {
    int port = 9111;
    std::shared_ptr<TSocket> socket(new TSocket("172.21.34.88", port));
    std::shared_ptr<TTransport> transport(
        new TFramedTransport(socket));  // for the noblockingserver

    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    transport->open();

    second_client = std::make_shared<ParaServClient>(protocol);
  }

  std::map<int64_t, std::string> tmp_kv;

  {
    total_files = 24;
    for (int i(0); i < total_files; i += 2) {
      col_index.push_back(i);
    }
  }

  second_client->copy_start(col_index, total_files);
  // second_client->pull(tmp_kv, fids);
  // auto it = fids.begin();
  // int64_t test_fid = *it;
  // if (key_vals.at(test_fid) == tmp_kv.at(test_fid)) {
  //     std::cout<<"The transport and copy start success!!!!"<<std::endl;
  // }
}

void TestServ::testSimplePush() {}

int main(int argc, char** argv) {
  string strPort = argv[1];
  int port = std::stoi(strPort);
  TestServ testServ(port);

  // std::cout << "test_start: " << std::endl;
  // testServ.test_start();

  // std::cout << "test_transport: " << std::endl;
  // testServ.test_transport();

  std::cout << "test_push: " << std::endl;
  testServ.test_push();

  std::cout << "test_pushemb: " << std::endl;
  testServ.test_pushemb();

  // std::cout << "test_pull: " << std::endl;
  // testServ.test_pull();

  // std::cout << "test_copy_start: " << std::endl;
  // testServ.test_copy_start();

  return 0;
}
