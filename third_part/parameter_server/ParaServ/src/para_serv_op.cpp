
#include "para_serv_op.h"

#include <city.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <thrift/processor/TMultiplexedProcessor.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/protocol/TMultiplexedProtocol.h>
#include <thrift/protocol/TProtocolDecorator.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <map>
#include <set>
#include <sstream>
#include <thread>
#include <typeinfo>
#include <utility>

#include "external_util.h"
#include "parameter_server/ParaServ/prometheus_util.h"
#include "psProxyServ.h"
#include "rocksdb/write_batch.h"
#include "tbb/scalable_allocator.h"
#include "timer.h"

using namespace ps;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

void ParaServOP::init() {
  logger->info("ParaServOP::init start");
  pCache_ = new TbbStringHashMap();
  pCacheSyncEmb_ = new TbbUint64HashMap();
  std::string remote_dir;
  if (conf->getvalueof("recover", remote_dir) && !remote_dir.empty()) {
    std::string cmd_clear_db_dir = "rm -fr " + conf->data_dir + "/*";
    logger->info("clear db cmd: {}", cmd_clear_db_dir);
    system(cmd_clear_db_dir.c_str());
  }

  rep_b = new ParaServDB(conf);
  rep_b->Open0();
  logger->info("column family num: {}", rep_b->cfHandles.size());

  for (auto cf : rep_b->cfHandles) {
    this->cfHandles.insert(std::pair<std::string, rocksdb::ColumnFamilyHandle*>(
        cf->GetName(), cf));
    logger->info("cf inited: {}", cf->GetName());
  }

  db = rep_b->db;
  fea_use_length = conf->slot_dim;

  std::string enable_ut;
  conf->getvalueof("enable_update_times", enable_ut);
  if (!enable_ut.empty()) {
    enable_update_times = true;
  } else {
    enable_update_times = false;
  }

  lastSwapTime_ = Timer::getNowInSecond();
  lastSwapTimeSyncEmb_ = lastSwapTime_;
  print_database_info();
  loopDumpThread = std::thread(&ParaServOP::batchDumpToDB, this);
  loopSyncEmbThread = std::thread(&ParaServOP::batchSyncEmb, this);
  logger->info("ParaServOP::init end");
}

void ParaServOP::batchDumpToDB() {
  while (true) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(kCheckSwapIntervalMs));
    scalable_allocation_command(TBBMALLOC_CLEAN_ALL_BUFFERS, 0);
    if (pCache_->empty()) {
      logger->info("batchDumpToDB: pCache_ is empty, continue to wait");
      continue;
    }
    long curTimeSecond = Timer::getNowInSecond();
    long diffTime = curTimeSecond - lastSwapTime_;
    if (pCache_->size() > kMaxCacheSize || diffTime > kMaxSwapIntervalSecond) {
      logger->info("batchDumpToDB: do swap cache");
      pSwapCache_ = pCache_;
      swapFlag_ = true;
      lastSwapTime_ = curTimeSecond;
      pCache_ = new TbbStringHashMap();
    } else {
      logger->info("batchDumpToDB: pCache_ is not full, continue to wait");
      continue;
    }
    logger->info("batchDumpToDB: start to dump data to db, item count: {}",
                 pSwapCache_->size());
    Timer writeTimer;
    writeTimer.setStartTime();
    rocksdb::WriteBatch batch;
    std::string strKey;
    size_t pos;
    std::string cfIndex;
    for (const auto& item : *pSwapCache_) {
      pos = item.first.find('_');
      if (pos == std::string::npos) {
        strKey = item.first;
      } else {
        strKey = item.first.substr(0, pos);
      }
      cfIndex = std::to_string(std::stoul(strKey) % total_files);
      batch.Put(cfHandles[cfIndex], item.first, item.second);
    }

    rocksdb::WriteOptions writeOptions;
    setRocksdbOpts(writeOptions);
    db->Write(writeOptions, &batch);
    // flush all cfs
    for (const auto& item : cfHandles) {
      CfHandleType cfHandle = item.second;
      db->Flush(rocksdb::FlushOptions(), cfHandle);
    }
    writeTimer.setEndTime();

    logger->info("batchDumpToDB: end dump data, time use in ms: {}",
                 writeTimer.getDiffTimeMilli());
    swapFlag_ = false;
    std::this_thread::sleep_for(
        std::chrono::milliseconds(kCheckSwapIntervalMs));
    delete pSwapCache_;
    pSwapCache_ = nullptr;
  }
}

void ParaServOP::batchSyncEmb() {
  while (true) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(kCheckSyncEmbIntervalMs));
    if (pCacheSyncEmb_->empty()) {
      logger->info("batchSyncEmb: pCacheSyncEmb_ is empty, continue to wait");
      continue;
    }
    long curTimeSecond = Timer::getNowInSecond();
    long diffTime = curTimeSecond - lastSwapTimeSyncEmb_;
    if (pCacheSyncEmb_->size() > kMaxCacheSyncEmbSize ||
        diffTime > kMaxSyncEmbIntervalSecond) {
      logger->info("batchSyncEmb: do swap pSwapCacheSyncEmb_");
      pSwapCacheSyncEmb_ = pCacheSyncEmb_;
      lastSwapTimeSyncEmb_ = curTimeSecond;
      pCacheSyncEmb_ = new TbbUint64HashMap();
    } else {
      logger->info(
          "batchSyncEmb: pCacheSyncEmb_ is not full, continue to wait");
      continue;
    }

    // wait for old pCacheSyncEmb_ consumed
    std::this_thread::sleep_for(
        std::chrono::milliseconds(kCheckSyncEmbIntervalMs));

    logger->info(
        "batchSyncEmb: start to sync data to online ps, item count: {}",
        pSwapCacheSyncEmb_->size());
    Timer syncEmbTimer;
    syncEmbTimer.setStartTime();
    syncEmb();
    syncEmbTimer.setEndTime();
    logger->info("batchSyncEmb: end syncEmb data, time use in ms: {}",
                 syncEmbTimer.getDiffTimeMilli());

    delete pSwapCacheSyncEmb_;
    pSwapCacheSyncEmb_ = nullptr;
  }
}

void ParaServOP::push(const std::map<Key, std::string>& key_vals,
                      bool is_sync) {
  logger->info("ParaServOP::push start, keys num: {}", key_vals.size());
  if (db_start_status_ != STARTED) {
    return;
  }
  Timer tPush;
  tPush.setStartTime();
  sync_client_lock.lock();
  std::shared_ptr<tcmcp_psProxyServClient> current_sync_client(sync_client);
  sync_client_lock.unlock();

  for (const auto& item : key_vals) {
    std::string cf_index(std::to_string(item.first % total_files));
    int slot = get_slot(item.first);

    float max_norm = conf->max_norm[slot];
    float learn = conf->learn_rate[slot];
    std::string opti_ = conf->optimazation[slot];

    const Key& fid = item.first;
    std::string strFid = std::to_string(fid);

    std::vector<float> vec_grad(str2vec(item.second));
    const size_t& val_size = vec_grad.size();
    Map<MatrixXf> grad(&vec_grad.at(0), 1, vec_grad.size());

    std::string values;
    MatrixXf ada_sum;  //(MatrixXf::Constant(1, val_size, ada_beta));
    bool succeed = false;

    if (isAda(opti_)) {
      succeed = getWithCache(cfHandles[cf_index], strFid + "_ada", values);
      if (!succeed) {
        logger->error("ParaServOP::push get key: {}, not exist in cache and db",
                      strFid + "_ada");
        return;
      }
      std::vector<float> tmp(str2vec(values));
      ada_sum = Map<MatrixXf>(&tmp.at(0), 1, tmp.size());
    }

    succeed = getWithCache(cfHandles[cf_index], strFid + "_emb", values);
    if (!succeed) {
      logger->error("ParaServOP::push get key: {}, not exist in cache and db",
                    strFid + "_emb");
      return;
    }
    std::vector<float> tmp2(str2vec(values));
    if (item.second.size() != values.size()) {
      logger->error(
          "Error msg: The dimensions of emb and grad must be equal, "
          "but get emb_dim = {}, grad_dim = ",
          values.size(), item.second.size());
      continue;
    }

    Map<MatrixXf> para_dict(&tmp2.at(0), 1, tmp2.size());
    if (opti_ == "adagrad") {
      ada_sum += grad.cwiseAbs2();
      para_dict -= learn * grad.cwiseProduct(
                               (ada_sum + MatrixXf::Constant(1, val_size, 1E-6))
                                   .cwiseSqrt()
                                   .cwiseInverse());
    } else if (opti_ == "rmsp") {
      ada_sum = conf->rmsp_beta * ada_sum + grad.cwiseAbs2();
      para_dict -=
          learn * grad.cwiseProduct((ada_sum.cwiseSqrt() +
                                     MatrixXf::Constant(1, val_size, 1E-7))
                                        .cwiseInverse());
    } else {
      para_dict -= learn * grad;
    }
    if (max_norm > 1E-6) {
      l2_norm_vec(para_dict, max_norm);
    }

    succeed =
        getWithCache(cfHandles[cf_index], strFid + "_update_times", values);
    int update_times = std::stoi(values) + 1;

    std::string strEmb = vec2str(para_dict);
    std::string strAda = vec2str(ada_sum);
    if (current_sync_client) {
      insertWithUpdateUnit64(fid, strEmb);
    }
    putCache(strFid, strEmb, opti_, strAda, update_times);
  }

  tPush.setEndTime();
  logger->info("ParaServOP::push end, time use in ms: {}",
               tPush.getDiffTimeMilli());
}

void ParaServOP::syncEmb() {
  if (pSwapCacheSyncEmb_->empty()) {
    logger->error("ParaServOP::syncEmb pSwapCacheSyncEmb_ empty, return");
    return;
  }
  std::map<Key, std::string> syncEmb;
  sync_client_lock.lock();
  std::shared_ptr<tcmcp_psProxyServClient> current_sync_client(sync_client);
  sync_client_lock.unlock();
  if (!current_sync_client) {
    logger->error("ParaServOP::syncEmb get emb connection failed, return");
    return;
  }
  for (const auto& item : *pSwapCacheSyncEmb_) {
    syncEmb.emplace(item.first, item.second);
  }
  current_sync_client->tcmcp_pushemb(syncEmb);
  logger->info("ParaServOP::syncEmb syncEmb complete, map size: {}",
               syncEmb.size());
}

void ParaServOP::pushemb(const std::map<Key, std::string>& key_vals) {
  logger->info("ParaServOP::pushemb start, keys num: {}", key_vals.size());
  Timer tPushemb;
  tPushemb.setStartTime();
  if (db_start_status_ != STARTED) {
    return;
  }

  for (const auto& key_val : key_vals) {
    auto& fid = key_val.first;
    const std::string strFid = std::to_string(fid);

    std::string cf_index(std::to_string(fid % total_files));
    std::string value;
    int update_times = 0;
    bool succeed =
        getWithCache(cfHandles[cf_index], strFid + "_update_times", value);
    if (!succeed) {
      update_times = 1;
    } else {
      update_times = std::stoi(value) + 1;
    }
    putCacheWithoutAda(strFid, key_val.second, update_times);
  }

  tPushemb.setEndTime();
  logger->info("ParaServOP::pushemb end, time use in ms: {}",
               tPushemb.getDiffTimeMilli());
}

void ParaServOP::pushada(const std::map<Key, std::string>& key_vals) {
  logger->info("ParaServOP::pushada start, keys num: {}", key_vals.size());
  Timer tPushada;
  tPushada.setStartTime();
  if (db_start_status_ != STARTED) {
    return;
  }
  for (auto it = key_vals.begin(); it != key_vals.end(); ++it) {
    auto& fid = it->first;
    std::string cf_index(std::to_string(fid % total_files));
    pCache_->insert(std::make_pair(std::to_string(fid) + "_ada", it->second));
  }
  tPushada.setEndTime();
  logger->info("ParaServOP::pushada end, time use in ms: {}",
               tPushada.getDiffTimeMilli());
}

void ParaServOP::pull(std::map<Key, std::string>& key_vals,
                      const std::set<Key>& keys) {
  return;
}

void ParaServOP::multi_pull(std::map<Key, std::string>& key_vals,
                            const std::set<Key>& keys) {
  logger->info("ParaServOP::multi_pull start, keys num: {}", keys.size());
  Timer tMultiPUll;
  tMultiPUll.setStartTime();

  auto prometheus = prometheus_util::Instance();

  std::vector<rocksdb::Slice> embKeyVec;
  std::vector<std::string> strKeyVec;
  std::vector<CfHandleType> cfHandleVec;
  std::vector<Key> keyVec;

  for (const auto& key : keys) {
    const std::string strFidEmb = std::to_string(key) + "_emb";
    TbbHashConstAccessor hashConstAccessor;
    if (pCache_->find(hashConstAccessor, strFidEmb)) {
      key_vals[key] = hashConstAccessor->second;
      continue;
    }
    if (swapFlag_) {
      if (pSwapCache_->find(hashConstAccessor, strFidEmb)) {
        key_vals[key] = hashConstAccessor->second;
        continue;
      }
    }

    keyVec.emplace_back(key);
    strKeyVec.emplace_back(strFidEmb);
    embKeyVec.emplace_back(strKeyVec.back());
    std::string col_index = std::to_string(key % total_files);
    cfHandleVec.emplace_back(cfHandles[col_index]);
  }

  logger->info(
      "ParaServOP::multi_pull total keys num: {}, keys num found in cache: {}, "
      "keys num need get from db: {}",
      keys.size(), keys.size() - cfHandleVec.size(), cfHandleVec.size());

  Timer t1;
  t1.setStartTime();
  std::vector<std::string> values;
  std::vector<rocksdb::Status> statusVec =
      db->MultiGet(rocksdb::ReadOptions(), cfHandleVec, embKeyVec, &values);
  t1.setEndTime();
  // prometheus->Set("multi_pull_multi_get", t1.getDiffTimeMilli());

  t1.setStartTime();
  for (size_t i(0); i < statusVec.size(); ++i) {
    Key fid = keyVec.at(i);
    const std::string strFid = std::to_string(fid);
    int slot = get_slot(keyVec.at(i));
    int _length = fea_use_length.at(slot);

    if (statusVec.at(i).IsNotFound()) {
      float max_norm, ada_beta;
      std::string opti_;
      max_norm = conf->max_norm.at(slot);
      ada_beta = conf->ada_beta;
      opti_ = conf->optimazation.at(slot);

      MatrixXf tmp(Truncated_MatrixRandNorm(0, 1. / sqrt(_length), 1, _length));
      l2_norm_vec(tmp, max_norm);

      std::string strEmb = vec2str(tmp);
      key_vals.insert(std::make_pair(keyVec.at(i), strEmb));
      putCache(strFid, strEmb, opti_,
               vec2str(MatrixXf::Constant(1, _length, ada_beta)), 0);
    } else {
      int old_size = values.at(i).size() / sizeof(float);
      if (old_size == _length) {  //维度一致
        key_vals.insert(std::make_pair(keyVec.at(i), values.at(i)));
      } else {
        logger->error(
            "Error msg: Dimensions are not equal! fid = {}, slot = {}, "
            "old_dim = {} , new dims = {}",
            fid, slot, old_size, _length);
        std::string strEmb;
        std::string strAda;
        std::string value;

        float max_norm = conf->max_norm.at(slot);
        float ada_beta = conf->ada_beta;
        rocksdb::Status status;
        std::string opti_ = conf->optimazation.at(slot);

        if (old_size < _length) {  //填充emb和_ada维度
          MatrixXf new_emb(Truncated_MatrixRandNorm(0, 1. / sqrt(_length), 1,
                                                    _length - old_size));
          l2_norm_vec(new_emb, max_norm);
          strEmb = values.at(i) + vec2str(new_emb);

          if (isAda(opti_)) {
            bool succeed = getWithCache(cfHandleVec[i], strFid + "_ada", value);
            if (!succeed) {
              logger->error("Error msg: get _ada message failed!");
              MatrixXf new_ada = MatrixXf::Constant(1, _length, ada_beta);
              strAda = vec2str(new_ada);
            } else {
              MatrixXf new_ada =
                  MatrixXf::Constant(1, _length - old_size, ada_beta);
              strAda = value + vec2str(new_ada);
            }
          }

        } else {  //裁剪emb和_ada维度
          strEmb = values.at(i).substr(0, _length * sizeof(float));

          if (isAda(opti_)) {
            bool succeed = getWithCache(
                cfHandleVec[i], std::to_string(keyVec[i]) + "_ada", value);
            if (!succeed) {
              logger->error("Error msg: get _ada message failed!");
              MatrixXf new_ada = MatrixXf::Constant(1, _length, ada_beta);
              strAda = vec2str(new_ada);
            } else {
              strAda = value.substr(0, _length * sizeof(float));
            }
          }
        }
        key_vals.insert(std::make_pair(keyVec.at(i), strEmb));
        putCache(strFid, strEmb, opti_, strAda, 0);
      }
    }
  }

  t1.setEndTime();

  tMultiPUll.setEndTime();
  prometheus->Set("multi_pull_all", tMultiPUll.getDiffTimeMilli());
  prometheus->push();
  logger->info(
      "ParaServOP::multi_pull end, key_vals num: {}, time use in ms: {}",
      key_vals.size(), tMultiPUll.getDiffTimeMilli());
}

void ParaServOP::setEmbWithLength(std::map<Key, std::string>& key_vals,
                                  const Key& key,
                                  const std::string& oldEmbStr) {
  int old_size = oldEmbStr.size() / sizeof(float);
  int length = 0;
  int slot = get_slot(key);
  auto meta_config = fea_use_length.find(slot);
  if (meta_config == fea_use_length.end()) {
    length = old_size;
    logger->error("slot {} is not configured", slot);
  } else {
    length = meta_config->second;
  }
  if (length == old_size) {
    key_vals.insert(std::make_pair(key, oldEmbStr));
  } else {
    logger->error(
        "Error msg: Dimensions are not equal! fid = {}, slot = {}, "
        "old_dim = {} , new dims = {}",
        key, slot, old_size, length);
    if (length > old_size) {
      MatrixXf new_emb(MatrixXf::Zero(1, length - old_size));
      key_vals.insert(std::make_pair(key, oldEmbStr + vec2str(new_emb)));
    } else {
      key_vals.insert(
          std::make_pair(key, oldEmbStr.substr(0, length * sizeof(float))));
    }
  }
}

// 根据update_times判断是否使用0填充emb，更新次数小采用0填充
bool ParaServOP::fillZeroByUpdateTimes(std::map<Key, std::string>& key_vals,
                                       const Key& key,
                                       const TbbStringHashMap& cache) {
  int slot = get_slot(key);
  TbbHashConstAccessor hashConstAccessor;
  int update_times_real = 0;
  if (cache.find(hashConstAccessor, std::to_string(key) + "_update_times")) {
    update_times_real = std::stoi(hashConstAccessor->second);
  }
  int update_std = conf->update_times[slot];
  // 如果更新次数小于配置值，则emb失真，用初始值填充
  if (update_times_real <= update_std) {
    MatrixXf tmp = MatrixXf::Zero(1, fea_use_length[slot]);
    key_vals.insert(std::make_pair(key, vec2str(tmp)));
    return true;
  }
  return false;
}

void ParaServOP::pull_online(std::map<Key, std::string>& key_vals,
                             const std::set<Key>& keys) {
  logger->info("ParaServOP::pull_online start, keys num: {}", keys.size());
  Timer tPullOnline;
  tPullOnline.setStartTime();

  std::vector<rocksdb::Slice> slices_emb;
  std::vector<rocksdb::Slice> slices_update;
  std::vector<std::string> keys_emb;
  std::vector<std::string> keys_update;
  std::vector<rocksdb::ColumnFamilyHandle*> emb_handle;
  std::vector<Key> key_list;

  long start, end;
  start = Timer::getNowInSecond();

  for (const auto& key : keys) {
    const std::string strFidEmb = std::to_string(key) + "_emb";
    TbbHashConstAccessor hashConstAccessor;
    if (pCache_->find(hashConstAccessor, strFidEmb)) {
      if (enable_update_times) {
        if (fillZeroByUpdateTimes(key_vals, key, *pCache_)) {
          continue;
        }
      }
      setEmbWithLength(key_vals, key, hashConstAccessor->second);
      continue;
    }
    if (swapFlag_) {
      if (pSwapCache_->find(hashConstAccessor, strFidEmb)) {
        if (enable_update_times) {
          if (fillZeroByUpdateTimes(key_vals, key, *pSwapCache_)) {
            continue;
          }
        }
        setEmbWithLength(key_vals, key, hashConstAccessor->second);
        continue;
      }
    }

    key_list.emplace_back(key);
    keys_emb.emplace_back(strFidEmb);
    slices_emb.emplace_back(keys_emb.back());
    keys_update.emplace_back(std::to_string(key) + "_update_times");
    std::string col_index = std::to_string(key % total_files);
    emb_handle.emplace_back(cfHandles[col_index]);
  }

  std::vector<std::string> values_update;
  std::vector<rocksdb::Status> status_update;
  if (enable_update_times) {
    for (std::string& key : keys_update) {
      slices_update.push_back(rocksdb::Slice(key));
    }
    status_update = db->MultiGet(rocksdb::ReadOptions(), emb_handle,
                                 slices_update, &values_update);
  }

  std::vector<std::string> embValueVec;
  std::vector<rocksdb::Status> status_emb = db->MultiGet(
      rocksdb::ReadOptions(), emb_handle, slices_emb, &embValueVec);

  end = Timer::getNowInSecond();
  if (end - start > 100) {
    logger->info("The multiGet takes {} ms", end - start);
  }

  for (size_t i = 0; i < status_emb.size(); ++i) {
    const Key& key = key_list[i];
    const std::string& embStr = embValueVec[i];
    int length = getLen(key);

    if (status_emb[i].IsNotFound()) {
      MatrixXf tmp(MatrixXf::Zero(1, length));
      key_vals.insert(std::make_pair(key, vec2str(tmp)));
    } else {
      std::string newEmbStr;
      if (enable_update_times) {
        int slot = get_slot(key);
        int update_times_real = std::stoi(values_update[i]);
        int update_std = conf->update_times[slot];
        // 如果更新次数小于配置值，则emb失真，用初始值填充
        if (update_times_real <= update_std) {
          MatrixXf tmp = MatrixXf::Zero(1, fea_use_length[slot]);
          key_vals.insert(std::make_pair(key, vec2str(tmp)));
          continue;
        }
      }
      setEmbWithLength(key_vals, key, embStr);
    }
  }

  end = Timer::getNowInSecond();
  if (end - start > 130) {
    logger->info("slow pull_online response {} ms", end - start);
  }
  tPullOnline.setEndTime();

  logger->info(
      "ParaServOP::pull_online end, key_vals num: {}, time use in ms: {}",
      key_vals.size(), tPullOnline.getDiffTimeMilli());
}

void ParaServOP::hearbeat(std::string& _return, const int& input) {
  static int cnt = 0;
  if (cnt == 0) {
    total_files = input;
  }
  _return = std::to_string(input);
  logger->info("heartbeat, input: {}  times: {}", input, ++cnt);
}

void ParaServOP::status_cmd(std::string& _return, const std::string& cmd,
                            const std::vector<std::string>& values) {
  logger->info("ParaServOP::status_cmd start");
  if (cmd == "checkout_start") {  // diserted
    if (db_start_status_ == STARTED || db_start_status_ == NOT_STARTED) {
      _return = db_start_status_ == STARTING  ? "STARTING"
                : db_start_status_ == STARTED ? "STARTED"
                                              : "NOT_STARTED";
    }
    int expected = NOT_STARTED;
    if (!db_start_status_.compare_exchange_strong(expected, STARTING)) {
      _return = db_start_status_ == STARTING  ? "STARTING"
                : db_start_status_ == STARTED ? "STARTED"
                                              : "NOT_STARTED";
    } else {
      _return = "STARTING_WITH_TOKEN";
    }
  } else if (cmd == "get_status") {  // diserted
    _return = db_start_status_ == STARTING  ? "STARTING"
              : db_start_status_ == STARTED ? "STARTED"
                                            : "NOT_STARTED";
  } else if (cmd == "set_started") {  // diserted
    db_start_status_ = STARTED;
    _return = "OK";
  } else if (cmd == "enable_update_times") {
    enable_update_times = true;
    logger->info("enable_update_times: the update_times flag is set");
  } else if (cmd == "disable_update_times") {
    enable_update_times = false;
    logger->info("disable_update_times: the update_times flag is unset");
  } else if (cmd == "dump_weight_bias") {
    logger->info("dump_weight_bias: begin");
    execute_dump_wb();
    logger->info("dump_weight_bias: end");
  } else {
    _return = "cmd not known: " + cmd;
    logger->info("cmd not known: {}", cmd);
  }
  logger->info("ParaServOP::status_cmd end");
}

void ParaServOP::start(const std::vector<int>& cfNumberList,
                       const int fileNum) {
  int expected = NOT_STARTED;
  if (!db_start_status_.compare_exchange_strong(expected, STARTING)) {
    int curr_status = db_start_status_.load();
    if (curr_status == STARTING) {
      std::unique_lock<std::mutex> wait_lock(start_wait_mtx_);
      while (start_wait_cond_.wait_for(wait_lock, std::chrono::seconds(1)) ==
             std::cv_status::timeout) {
        if (db_start_status_.load() == STARTED) {
          break;
        }
      }
    } else {
      ;
    }
    return;
  }

  logger->info("ParaServOP::start: cfNum: {}, fileNum: {}", cfNumberList.size(),
               fileNum);
  execute_start(cfNumberList, fileNum);
  print_database_info();
  db_start_status_ = STARTED;
  std::unique_lock<std::mutex> release_lock(start_notify_mtx_);
  start_wait_cond_.notify_all();
  logger->info("ParaServOP::start end");
}

void ParaServOP::execute_start(const std::vector<int>& cfNumberList,
                               const int& tot_files) {
  logger->info("ParaServOP::execute_start start");
  total_files = tot_files;
  rocksdb::Options dbOptions;
  conf->setDBOptions(dbOptions);
  conf->printDBOptions(dbOptions);

  std::string remote_dir, abs_snap_dir;
  if (conf->getvalueof("recover", remote_dir) && remote_dir != "") {
    logger->info("system is copying data, recovering from {}", remote_dir);
    abs_snap_dir = copy_data_from_backup(cfNumberList, remote_dir);
    backup_start(abs_snap_dir, tot_files);
  } else {
    for (const auto& cfNumber : cfNumberList) {
      std::string cfName = std::to_string(cfNumber);
      rocksdb::ColumnFamilyHandle* cfHandle;
      if (cfHandles.count(cfName) != 1) {
        rocksdb::Status status =
            db->CreateColumnFamily(dbOptions, cfName, &cfHandle);
        if (status.ok()) {
          cfHandles[cfName] = cfHandle;
        } else {
          logger->error("CreateColumnFamily {} failed, reason: {}", cfName,
                        status.ToString().data());
        }
      }
    }
  }
}

int ParaServOP::execute_dump_wb() {
  static mutex m;
  std::lock_guard<std::mutex> _m(m);

  int key_count = 0;
  std::string file_name = conf->data_dir + "/weight_bias.dump";

  FILE* fp = fopen(file_name.c_str(), "w");
  if (fp == nullptr) {
    logger->error("execute_dump_wb failed: file not open");
  }

  rocksdb::ReadOptions readOptions;
  readOptions.snapshot = db->GetSnapshot();

  for (auto iter = cfHandles.begin(); iter != cfHandles.end(); iter++) {
    rocksdb::Iterator* it = db->NewIterator(readOptions, iter->second);

    for (it->SeekToFirst(); it->Valid(); it->Next()) {
      key_count++;
      string key = it->key().ToString();
      if (key.rfind("_emb") == string::npos) {
        continue;
      }
      int64_t key64 = stoll(key.substr(0, key.length() - 4));
      int slot = get_slot(key64);
      if (slot > 1200) {
        string output;
        std::vector<float> result = str2vec(it->value().ToString());
        for (size_t i = 0; i < result.size(); i++) {
          output += to_string(result[i]);
          if (i < result.size() - 1) output += ",";
        }
        fprintf(fp, "%d|%ld|%s\n", slot, key64, output.c_str());
      }
    }
    assert(it->status().ok());
    delete it;
  }

  fclose(fp);
  return 0;
}

/**
 * @note: make dir of model name in the remote machine. Then scp the file to
 * remote mochine. using this strategy to split each model.
 */
void ParaServOP::remote_mkdir(
    const std::map<std::string, std::string>& col_ip) {
  logger->info("ParaServOP::remote_mkdir start");
  std::string remote_dir("/data/transport/");
  std::string mn_id;
  conf->getmodelname(mn_id);
  remote_dir += mn_id;
  std::set<std::string> ips;
  for (auto& val : col_ip) {
    ips.insert(val.second);
  }
  logger->info("=============remote_mkdir==================");
  for (auto& ip : ips) {
    std::string mkdir_command("ssh -o StrictHostKeyChecking=no ");
    mkdir_command += ip;
    mkdir_command += " \'mkdir -p /data/transport/";
    mkdir_command += mn_id;
    mkdir_command += ";\n exit\'";
    logger->info("whole command is: {}", mkdir_command);
    system(mkdir_command.data());
    logger->info("make dir in {} success!", ip);
  }
  logger->info("ParaServOP::remote_mkdir end");
}

void ParaServOP::transport(const std::map<std::string, std::string>& col_ip) {
  logger->info("ParaServOP::transport start");
  std::string recover_dir;
  if (conf->getvalueof("recover", recover_dir) && recover_dir != "") {
    logger->error("skip transport: the recover directory is {}", recover_dir);
    return;
  }

  bool expected = false;
  if (!is_transporting_.compare_exchange_strong(expected, true)) {
    logger->error("transporting data, do not transport again");
    return;
  }
  remote_mkdir(col_ip);
  std::string mn_id;
  conf->getmodelname(mn_id);

  rocksdb::Checkpoint* checkpoint;
  rocksdb::Status status = rocksdb::Checkpoint::Create(db, &checkpoint);
  rocksdb::Env* env = db->GetEnv();
  std::string snap_dir = conf->data_dir + "/snap";
  status = env->CreateDir(snap_dir);
  logger->info("snap_dir: {}", snap_dir);
  if (!status.ok()) {
    logger->error("snap_dir has exist");
    return;
  }

  for (auto& tmp_handle : cfHandles) {
    rocksdb::ExportImportFilesMetaData* metadata = nullptr;
    std::string col_dir = snap_dir + "/" + tmp_handle.first;
    status =
        checkpoint->ExportColumnFamily(tmp_handle.second, col_dir, &metadata);
    assert(status.ok());

    auto j_meta = get_json_from_sstmeta(*metadata);
    std::string file_name = col_dir + "/" + "metafile";
    std::ofstream metafile(file_name);
    metafile << j_meta;
    metafile.close();

    std::string scp_command("scp -o StrictHostKeyChecking=no -r ");
    auto col_ip_it = col_ip.find(tmp_handle.first);
    if (col_ip_it == col_ip.end()) {
      logger->error("The column of {} has no destination.", tmp_handle.first);
      continue;
    }

    scp_command = scp_command + col_dir + " " + col_ip_it->second +
                  ":/data/transport/" + mn_id;
    logger->info("begin transport: {}", col_dir);
    system(scp_command.data());
    logger->info("end transport: {}", col_dir);
  }

  std::string rm_command("rm -rf ");
  rm_command += snap_dir;
  system(rm_command.data());
  is_transporting_ = false;
  logger->info("ParaServOP::transport end");
}

void ParaServOP::backup(std::string& _return, const std::string& backup_type,
                        const std::string& sub_dir,
                        const std::map<std::string, std::string>& col_ip) {
  logger->info("ParaServOP::backup start");
  bool expected = false;
  if (!is_transporting_.compare_exchange_strong(expected, true)) {
    _return = "doing backup, don't trigger again";
    logger->info("doing backup, don't trigger again");
    return;
  }
  logger->info("ready to do backup");
  std::string mn_id;
  conf->getmodelname(mn_id);

  std::string snap_dir;
  std::string dest_dir;
  std::shared_ptr<storage_tool> hdfs = storage_tool::Instance();

  snap_dir = hdfs->storage_path;

  snap_dir += "/";
  snap_dir += mn_id;
  if (sub_dir != "") {
    snap_dir += "/";
    snap_dir += sub_dir;
  }

  logger->info("backup dir is: {}", snap_dir);
  if (backup_type == "nfs" || hdfs->storage_type == "nfs") {
    // do nothing
  } else if (backup_type == "scp" || backup_type == "scp" ||
             backup_type == "oss" || backup_type == "oss") {
    dest_dir = snap_dir;
    snap_dir = conf->data_dir + "/backup";
    if (sub_dir != "") {
      snap_dir += "/";
      snap_dir += sub_dir;
    }
    logger->info("tmp backup dir is: {}", snap_dir);
    std::string mkdir_cmd = std::string("mkdir -p ") + snap_dir;
    system(mkdir_cmd.c_str());
  } else {
    _return = "not supported storage type";
    is_transporting_ = false;
    return;
  }

  rocksdb::Checkpoint* checkpoint;
  rocksdb::Status status = rocksdb::Checkpoint::Create(db, &checkpoint);
  rocksdb::Env* env = db->GetEnv();

  hdfs->remote_make_clear_dir((mn_id + "/" + sub_dir).c_str());

  for (auto& tmp_handle : cfHandles) {
    auto col_ip_it = col_ip.find(tmp_handle.first);
    if (col_ip_it == col_ip.end()) {
      logger->info("The column of {} has no destination.", tmp_handle.first);
      continue;
    }

    rocksdb::ExportImportFilesMetaData* metadata = nullptr;
    std::string cf_name = tmp_handle.first;
    std::string col_dir = snap_dir + "/" + cf_name;
    env->DeleteDir(col_dir);
    status =
        checkpoint->ExportColumnFamily(tmp_handle.second, col_dir, &metadata);
    if (!status.ok()) {
      logger->error("export cf failed, cf: {}, reason: {}", cf_name,
                    status.ToString().data());
    }

    auto j_meta = get_json_from_sstmeta(*metadata);
    std::string file_name = col_dir + "/" + "metafile";
    std::ofstream metafile(file_name);
    metafile << j_meta;
    metafile.close();

    hdfs->storage_tool_upload((mn_id + "/" + sub_dir).c_str(), cf_name.c_str(),
                              col_dir.c_str());
  }
  system((std::string("rm -fr ") + snap_dir).c_str());
  is_transporting_ = false;
  _return = "OK";
  logger->info("ParaServOP::backup end");
}

std::string ParaServOP::copy_data_from_backup(
    const std::vector<int>& cfNumberList, const std::string& remote_dir) const {
  logger->info("ParaServOP::copy_data_from_backup start");
  std::string mn_id;
  conf->getmodelname(mn_id);
  std::shared_ptr<storage_tool> hdfs = storage_tool::Instance();

  std::string rel_data_dir = conf->data_dir;
  std::string start_dir;
  std::string model_snap_dir = mn_id + "/" + remote_dir;

  if (hdfs->storage_type == "nfs") {
    start_dir = hdfs->storage_path;
    start_dir += "/";
    start_dir += model_snap_dir;
    start_dir += "/";
  } else if (hdfs->storage_type == "scp" || hdfs->storage_type == "oss") {
    start_dir = conf->data_dir + "/backup-start/";
    if (remote_dir.empty()) {
      logger->info("snap name is not defined");
      return "";
    }
    system((std::string("mkdir -p ") + start_dir).c_str());
    system((std::string("rm -fr ") + start_dir + "*").c_str());

    for (int col : cfNumberList) {
      std::string cfName(to_string(col));
      std::string cf_remote_dir = remote_dir + "/" + cfName;
      hdfs->storage_tool_download(cf_remote_dir.c_str(), cfName.c_str(),
                                  start_dir.c_str());
    }
  }
  logger->info("ParaServOP::copy_data_from_backup end");
  return start_dir;
}

void ParaServOP::backup_start(std::string abs_snap_dir, int cf_count) {
  logger->info("ParaServOP::backup_start start");
  std::string start_dir = std::move(abs_snap_dir);
  for (int col = 0; col < cf_count; col++) {
    logger->info("cfName: {}", col);
    std::string cfName = std::to_string(col);
    std::string col_dir = start_dir + cfName;
    std::string metafile_name(col_dir + "/metafile");
    std::ifstream metafile(metafile_name);
    if (!metafile.is_open()) {
      logger->error("cfName: {}, no meta: {}", col, metafile_name);
      continue;
    }
    json j_meta;
    metafile >> j_meta;
    metafile.close();
    if (j_meta.empty()) {
      logger->info("empty meta: {}", metafile_name);
      continue;
    }
    if (!j_meta.contains("files") || j_meta["files"].size() == 0) {
      continue;
    }
    for (auto& file : j_meta["files"]) {
      file["db_path"] = col_dir;
      file["column_family_name"] = cfName;
    }

    rocksdb::ExportImportFilesMetaData metadata(get_sstmeta_from_json(j_meta));
    rocksdb::ColumnFamilyHandle* cfHandle = nullptr;
    rocksdb::ImportColumnFamilyOptions i_options;
    rocksdb::Status status;
    rocksdb::ColumnFamilyOptions cf_option;

    try {
      status = db->CreateColumnFamilyWithImport(cf_option, cfName, i_options,
                                                metadata, &cfHandle);
    } catch (std::exception& e) {
      logger->info("exception caught: {}", e.what());
      continue;
    }
    if (status.ok()) {
      logger->info("success create the {} cf", cfName);
    } else {
      logger->error("can't create the {} cf", cfName);
      assert(0);
    }
    cfHandles.insert(std::make_pair(cfName, cfHandle));
    fflush(nullptr);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  logger->info("ParaServOP::backup_start end");
}

void ParaServOP::start_sync_client(const std::string& url,
                                   const std::string& path) {
  logger->info("ParaServOP::start_sync_client start");
  int thread_num;
  conf->getthreadnum(thread_num);
  thread_num = 3;
  auto client = std::shared_ptr<tcmcp_psProxyServClient>(
      new tcmcp_psProxyServClient(url, path, thread_num, 5000));
  if (client->init()) {
    logger->error("sync client init failed, url: {}, path: {}", url, path);
    return;
  }
  sync_client_lock.lock();
  sync_client = client;
  sync_client_lock.unlock();
  logger->info("ParaServOP::start_sync_client end");
}

void ParaServOP::stop_sync_client(const std::string& url,
                                  const std::string& path) {
  logger->info("ParaServOP::stop_sync_client start");
  sync_client_lock.lock();
  sync_client.reset();
  sync_client_lock.unlock();
  logger->info("ParaServOP::stop_sync_client end");
}

void ParaServOP::copy_start(const std::vector<int>& cfNumberList,
                            const int& tot_files) {
  // discard
}

void ParaServOP::del(const std::set<Key>& keys) {}

int ParaServOP::print_database_info() {
  logger->info("ParaServOP::print_database_info start");
  if (!db) {
    logger->error("rocksdb not opened");
    return 0;
  }

  logger->info("rocksdb opened, last seq is {}", db->GetLatestSequenceNumber());
  return 0;
}
