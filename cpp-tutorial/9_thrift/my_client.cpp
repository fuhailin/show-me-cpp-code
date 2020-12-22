#include "gen-cpp/Greeter.h"
#include "gen-cpp/benchmark_types.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <numeric>
#include <string>
#include <sys/time.h>
#include <thread>
#include <vector>

#define PORT 9090
#define HOST "localhost"

using namespace std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using boost::shared_ptr;

mutex mtx;

int64_t get_current_time()
{
  struct timeval tv;
  gettimeofday(&tv, NULL); //该函数在sys/time.h头文件中
  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

BenchmarkMessage prepare_args()
{
  bool b = true;
  int i = 100000;
  string str = "许多往事在眼前一幕一幕，变的那麼模糊";
  BenchmarkMessage msg;
  msg.__set_field1(str);
  msg.__set_field2(i);
  msg.__set_field3(i);
  msg.__set_field4(str);
  msg.__set_field5(i);
  msg.__set_field6(i);
  msg.__set_field7(str);
  msg.__set_field9(str);
  msg.__set_field12(b);
  msg.__set_field13(b);
  msg.__set_field14(b);
  msg.__set_field16(i);
  msg.__set_field17(b);
  msg.__set_field18(str);
  msg.__set_field22(i);
  msg.__set_field23(i);
  msg.__set_field24(b);
  msg.__set_field25(i);
  msg.__set_field29(i);
  msg.__set_field30(b);
  msg.__set_field59(b);
  msg.__set_field60(i);
  msg.__set_field67(i);
  msg.__set_field68(i);
  msg.__set_field78(b);
  msg.__set_field80(b);
  msg.__set_field81(b);
  msg.__set_field100(i);
  msg.__set_field101(i);
  msg.__set_field102(str);
  msg.__set_field103(str);
  msg.__set_field104(i);
  msg.__set_field128(i);
  msg.__set_field129(str);
  msg.__set_field130(i);
  msg.__set_field131(i);
  msg.__set_field150(i);
  msg.__set_field271(i);
  msg.__set_field272(i);
  msg.__set_field280(i);

  return msg;
}

int main(int argc, char **argv)
{
  cout << "startup" << endl;
  if (argc <= 1)
  {
    cout << "no parms" << endl;
    return -1;
  }
  int threads_num = atoi(argv[1]);
  int requests_num = atoi(argv[2]);

  cout << "prepare BenchmarkMessage" << endl;
  BenchmarkMessage msg = prepare_args();

  int per_client_num = requests_num / threads_num;

  atomic<int> trans(0);
  atomic<int> trans_ok(0);

  vector<uint64_t> stats;
  int64_t start_time = get_current_time();

  for (int i = 0; i < threads_num; i++)
  {
    // cout << i << endl;
    thread t([i, per_client_num, &msg, &trans, &trans_ok, &stats]() {
      stdcxx::shared_ptr<TTransport> socket(new TSocket("localhost", PORT));
      stdcxx::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
      stdcxx::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
      GreeterClient client(protocol);
      transport->open();
      vector<uint64_t> stat;
      for (int j = 0; j < per_client_num; j++)
      {
        BenchmarkMessage return_msg;
        int64_t thread_start = get_current_time();
        client.say(return_msg, msg);
        // cout << "say" << i << endl;
        int64_t thread_get_response = get_current_time();
        stat.push_back(thread_get_response - thread_start);
        trans++;
        if (return_msg.field1.compare("OK") == 0)
        {
          trans_ok++;
        }
      }
      mtx.lock();
      stats.insert(stats.end(), stat.begin(), stat.end());
      mtx.unlock();
    });
    t.detach();
  }

  while (trans.load() < requests_num)
  {
    this_thread::sleep_for(chrono::milliseconds(10));
  }
  double cost_time = (get_current_time() - start_time) / 1000.0;
  while (stats.size() < (size_t)requests_num)
  {
    this_thread::sleep_for(chrono::milliseconds(10));
  }

  sort(stats.begin(), stats.end());

  double mean = accumulate(stats.begin(), stats.end(), 0.0) / stats.size();
  
  cout << "sent     requests    : " << requests_num << endl;
  cout << "received requests    : " << trans << endl;
  cout << "received requests_OK : " << trans_ok << endl;
  cout << "mean(ms):   " << mean << endl;
  cout << "median(ms): " << stats[stats.size() / 2] << endl;
  cout << "max(ms):    " << *(stats.end() - 1) << endl;
  cout << "min(ms):    " << *(stats.begin()) << endl;
  cout << "99P(ms):    " << stats[int(stats.size() * 0.999)] << endl;

  cout << "time cost(s)       :" << cost_time << endl;
  if (cost_time > 0)
    cout << "throughput (TPS): " << (double)requests_num / cost_time << endl;

  return 0;
}