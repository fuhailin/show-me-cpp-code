#include <ps/ps.h>
// #include <dmlc/parameter.h>
#include <dmlc/base.h>
// #include <dmlc/data.h>
// #include <dmlc/io.h>
#include <algorithm>
#include <dmlc/logging.h>
#include <iostream>
#include <map>
#include <stack>
#include <stdlib.h>
#include <unistd.h>
#include <unordered_set>
#include <vector>

using namespace ps;
using namespace std;
using namespace dmlc;

// key for request command
enum kCmd { ITER_FINISH, INIT_PARAM, DUMP_MODEL, UPDATE };

// =============================== LrParam
// ======================================= //
struct LrParam : public dmlc::Parameter<LrParam> {
  float learning_rate;
  int max_delay;
  int max_iter;
  int batch_size;
  string train_path;
  string test_path;
  string model_path;

  DMLC_DECLARE_PARAMETER(LrParam) {
    DMLC_DECLARE_FIELD(learning_rate)
        .set_lower_bound(0.0f)
        .set_default(0.1f)
        .describe("learning_rate");
    DMLC_DECLARE_FIELD(max_delay).set_lower_bound(0).set_default(0).describe(
        "max_delay");
    DMLC_DECLARE_FIELD(max_iter).set_lower_bound(1).set_default(3).describe(
        "max_iter");
    DMLC_DECLARE_FIELD(batch_size)
        .set_lower_bound(1)
        .set_default(100)
        .describe("batch_size");
    DMLC_DECLARE_FIELD(train_path).describe("train_path");
    DMLC_DECLARE_FIELD(test_path).describe("test_path");
    DMLC_DECLARE_FIELD(model_path).describe("model_path");
  }
};

// register it in cc file
DMLC_REGISTER_PARAMETER(LrParam);

void initLrParam(LrParam &param, int argc, char *argv[]) {
  map<string, string> kwargs;
  char name[256], val[256];
  for (int i = 0; i < argc; ++i) {
    if (sscanf(argv[i], "%[^=]=%[^\n]", name, val) == 2) {
      kwargs[name] = val;
    }
  }
  param.Init(kwargs);
}
// =============================== LrParam
// ======================================= //

// =============================== LrModel
// ======================================= //
class LrModel {
public:
  LrModel(const unordered_set<index_t> &keySet, LrParam *param,
          KVWorker<float> *kv) {
    srand(MyRank());
    kv_ = kv;
    param_ = param;
    for (auto key : keySet) {
      keys_.push_back(key);
    }
    sort(keys_.begin(), keys_.end());
    for (size_t i = 0; i < keys_.size(); ++i) {
      index_map_[keys_[i]] = i;
    }
    vals_.resize(keys_.size());
    for (size_t i = 0; i < vals_.size(); ++i) {
      vals_[i] = (1.0 * rand() / RAND_MAX) * 0.1 - 0.05;
    }
    kv_->Wait(kv_->Push(keys_, vals_, lens_, INIT_PARAM));
    Postoffice::Get()->Barrier(kWorkerGroup);
  }

  void train(const RowBlock<index_t> &batch) {
    kv_->Wait(kv_->Pull(keys_, &vals_));
    unordered_map<Key, float> grad;
    for (size_t i = 0; i < batch.size; ++i) {
      const auto &sample = batch[i];
      float sum = 0;
      for (size_t j = 0; j < sample.length; ++j) {
        sum += vals_[keys_[index_map_[sample.index[j]]]];
      }
      float pre = 1.0 / (1.0 + exp(-sum));
      for (size_t j = 0; j < sample.length; ++j) {
        grad[sample.index[j]] += pre - sample.label;
      }
    }
    vector<Key> ks;
    ks.reserve(grad.size());
    vector<float> vs(grad.size());
    for (auto it = grad.begin(); it != grad.end(); ++it) {
      ks.push_back(it->first);
    }
    sort(ks.begin(), ks.end());
    for (size_t i = 0; i < ks.size(); ++i) {
      vs[i] = grad[ks[i]] / batch.size;
    }
    kv_->Wait(kv_->Push(ks, vs, lens_, UPDATE));
    kv_->Wait(kv_->Request(ITER_FINISH, "", kScheduler));
  }

  virtual ~LrModel() {
    if (kv_) {
      cout << "ended" << endl;
      delete kv_;
    }
  }

private:
  KVWorker<float> *kv_;
  vector<float> vals_;
  vector<Key> keys_;
  vector<int> lens_;
  LrParam *param_;
  unordered_map<index_t, index_t> index_map_;
};
// =============================== LrModel
// ======================================= //

// =============================== Server
// ======================================= //
template <typename Val> class KVStoreServer {
public:
  KVStoreServer(LrParam *param) {
    using namespace std::placeholders;
    ps_server_ = new ps::KVServer<float>(0);
    ps_server_->set_request_handle(
        std::bind(&KVStoreServer::DataHandle, this, _1, _2, _3));
    param_ = param;
  }

  ~KVStoreServer() {
    if (ps_server_) {
      delete ps_server_;
    }
  }

private:
  void DataHandle(const KVMeta &req_meta, const KVPairs<Val> &req_data,
                  KVServer<Val> *server) {
    size_t n = req_data.keys.size();
    cout << "key'length = " << n << endl;
    if (req_meta.push) {
      cout << "val's length = " << req_data.vals.size() << endl;
      CHECK_EQ(n, req_data.vals.size());
      if (req_meta.cmd == INIT_PARAM) {
        cout << "init param" << endl;
        for (size_t i = 0; i < n; ++i) {
          weight_[req_data.keys[i]] = req_data.vals[i];
        }
        server->Response(req_meta);
      } else if (req_meta.cmd == UPDATE) {
        for (size_t i = 0; i < n; ++i) {
          weight_[req_data.keys[i]] -= param_->learning_rate * req_data.vals[i];
        }
        server->Response(req_meta);
      } else if (req_meta.cmd == DUMP_MODEL) {
        cout << "dump_model" << endl;
        char path[256];
        sprintf(path, "%s/%05d", param_->model_path.c_str(), MyRank());
        dmlc::Stream *fo = dmlc::Stream::Create(path, "w");
        {
          dmlc::ostream os(fo);
          for (auto it = weight_.begin(); it != weight_.end(); ++it) {
            if (fabs(it->second) > 1e-10) {
              os << it->first << " " << it->second << endl;
            }
          }
        }
        delete fo;
        server->Response(req_meta);
      }
    } else {
      KVPairs<Val> response;
      response.keys = req_data.keys;
      response.vals.resize(n);
      for (size_t i = 0; i < n; ++i) {
        response.vals[i] = weight_[i];
      }
      server->Response(req_meta, response);
    }
  }

  unordered_map<Key, Val> weight_;
  LrParam *param_;
  KVServer<float> *ps_server_;
};

void RunServer(const LrParam &param) {
  if (!IsServer()) {
    return;
  }
  std::cout << "is server" << std::endl;
  auto server = new KVStoreServer<float>(const_cast<LrParam *>(&param));
  RegisterExitCallback([server]() {
    cout << "ended!" << endl;
    delete server;
  });
}
// =============================== Server
// ======================================= //

// =============================== Worker
// ======================================= //
void RunWorker(const LrParam &param) {
  if (!IsWorker()) {
    return;
  }
  std::cout << "is worker" << std::endl;
  int rank = MyRank();
  int num_workers = NumWorkers();
  // read data
  RowBlockIter<index_t> *data = RowBlockIter<index_t>::Create(
      param.train_path.c_str(), rank, num_workers, "libsvm");
  // getKeySet
  unordered_set<index_t> indexSet;
  data->BeforeFirst();
  while (data->Next()) {
    const auto &batch = data->Value();
    for (size_t i = 0; i < batch.size; ++i) {
      auto v = batch[i];
      for (size_t j = 0; j < v.length; ++j) {
        indexSet.insert(v.index[j]);
      }
    }
  }
  cout << "indexSet = " << indexSet.size() << endl;
  KVWorker<float> *kv = new KVWorker<float>(0);
  vector<Key> keys(indexSet.size());
  LrModel model(indexSet, const_cast<LrParam *>(&param), kv);
  for (size_t i = 0; i < param.max_iter; ++i) {
    data->BeforeFirst();
    while (data->Next()) {
      const auto &batch = data->Value();
      for (size_t i = 0; i + param.batch_size < batch.size;
           i += param.batch_size) {
        model.train(batch.Slice(i, i + param.batch_size));
      }
    }
  }
  Postoffice::Get()->Barrier(kWorkerGroup);
  // dump model
  auto key_range = Postoffice::Get()->GetServerKeyRanges();
  vector<Key> kServerBegin;
  for (auto range : key_range) {
    kServerBegin.push_back(range.begin());
  }
  vector<float> vs(kServerBegin.size());
  vector<int> lens;
  kv->Wait(kv->Push(kServerBegin, vs, lens, DUMP_MODEL));
  cout << "ended!" << endl;
}
// =============================== Worker
// ======================================= //

// =============================== Scheduler
// ======================================= //
struct SchedulerRequestHandle {
  int minIterCount;
  int minIter;
  vector<int> iterCount;
  int delay;
  stack<SimpleData> blockedReqs;

  SchedulerRequestHandle(const LrParam &param)
      : minIterCount(NumWorkers()), minIter(0), iterCount(NumWorkers()),
        delay(param.max_delay) {}

  void operator()(const SimpleData &req, SimpleApp *app) {
    if (req.head == ITER_FINISH) {
      int rank = Postoffice::Get()->IDtoRank(req.sender);
      int iter = ++iterCount[rank];
      std::cout << "rank = " << rank << ", iter = " << iter << " request"
                << std::endl;
      if (iter - minIter > delay) {
        std::cout << "rank = " << rank << ", iter = " << iter << " delay"
                  << std::endl;
        blockedReqs.push(req);
      } else {
        app->Response(req);
        std::cout << "Response " << rank << std::endl;
      }
      if (iter == minIter + 1) {
        minIterCount--;
      }
      if (minIterCount == 0) {
        minIterCount = NumWorkers();
        minIter++;
        while (!blockedReqs.empty()) {
          auto top = blockedReqs.top();
          app->Response(top);
          std::cout << "Response " << Postoffice::Get()->IDtoRank(top.sender)
                    << std::endl;
          blockedReqs.pop();
        }
        for (int it : iterCount) {
          minIterCount -= (it > minIter);
        }
      }
    }
  }
};

void RunScheduler(const LrParam &param) {
  if (!IsScheduler()) {
    return;
  }
  std::cout << "is scheduler" << std::endl;
  auto schedulerApp = new SimpleApp(0);
  schedulerApp->set_request_handle(SchedulerRequestHandle(param));
  RegisterExitCallback([schedulerApp]() { delete schedulerApp; });
}
// =============================== Scheduler
// ======================================= //

int main(int argc, char *argv[]) {
  LrParam param;
  initLrParam(param, argc, argv);
  RunServer(param);
  RunScheduler(param);
  Start();
  RunWorker(param);
  Finalize();
  return 0;
}