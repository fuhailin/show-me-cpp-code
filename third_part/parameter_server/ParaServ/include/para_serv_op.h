
#ifndef PARA_SERV_OP_H
#define PARA_SERV_OP_H

#include <city.h>

#include <Eigen/Dense>
#include <atomic>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/bind.hpp>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "config.h"
#include "nlohmann/json.hpp"
#include "para_serv_types.h"
#include "ps_util.h"
#include "psconfigure.h"
#include "replication.h"
#include "rocksdb/db.h"
#include "tbb/concurrent_hash_map.h"
#include "tcmcp_psProxyServ.h"
#include "time_function.h"
#include "timer.h"

using namespace Eigen;
using json = nlohmann::json;

const int kFileNum = 24;  // 文件数目

class ParaServDB : public RockServerBase {
 public:
  ParaServDB(ps::Configure* conf) : RockServerBase(conf) {}
};

namespace ps {

class ParaServOP {
 public:
  using CfHandleType = rocksdb::ColumnFamilyHandle*;
  using TbbStringHashMap = tbb::concurrent_hash_map<std::string, std::string>;
  using TbbHashConstAccessor = TbbStringHashMap::const_accessor;
  using TbbHashAccessor = TbbStringHashMap::accessor;
  using TbbUint64HashMap = tbb::concurrent_hash_map<uint64_t, std::string>;
  using TbbUint64HashAccessor = TbbUint64HashMap::accessor;
  static const uint64_t kMaxCacheSize = 64 * 1024;
  const long kMaxSwapIntervalSecond = 60L;
  const long kCheckSwapIntervalMs = 1000L;

  static const uint64_t kMaxCacheSyncEmbSize = 8 * 1024;
  const long kMaxSyncEmbIntervalSecond = 10L;
  const long kCheckSyncEmbIntervalMs = 500L;

  std::unordered_map<std::string, CfHandleType> cfHandles;
  rocksdb::DB* db;
  ParaServDB* rep_b;

  int total_files;
  std::unordered_map<int, int> fea_use_length;
  std::atomic<bool> enable_update_times;

  // The client used to sync data to another cluster
  std::mutex sync_client_lock;
  std::shared_ptr<tcmcp_psProxyServClient> sync_client;

  void remote_mkdir(const std::map<std::string, std::string>& col_ip);

  Configure* conf;

  // db start/transport status
  enum { NOT_STARTED = 0, STARTING, STARTED };
  std::atomic<int> db_start_status_;
  std::atomic<bool> is_transporting_;
  std::mutex start_wait_mtx_, start_notify_mtx_;
  std::condition_variable start_wait_cond_;
  std::atomic<int> concurrent_push_count;

  ParaServOP()
      : db_start_status_(NOT_STARTED),
        is_transporting_(false),
        concurrent_push_count(0) {}

  ~ParaServOP() { delete db; }

  void init();

  void push(const std::map<Key, std::string>& key_vals, bool is_sync);

  void pushemb(const std::map<Key, std::string>& key_vals);

  void pushada(const std::map<Key, std::string>& key_vals);

  void pull(std::map<Key, std::string>& key_vals, const std::set<Key>& keys);

  void multi_pull(std::map<Key, std::string>&, const std::set<Key>&);

  void pull_online(std::map<Key, std::string>& Vals, const std::set<Key>& keys);

  void hearbeat(std::string& _return, const int& input);

  void status_cmd(std::string& _return, const std::string& cmd,
                  const std::vector<std::string>& values);

  /**
   * @note: In the cluster mode, at first the proxy will send information to all
   * of the nodes and all the nodes start serving with the start function.
   */
  void start(const std::vector<int>& col_num, const int tot_files);
  void execute_start(const std::vector<int>& col_num, const int& tot_files);

  /**
   * @note: transport the column from one cluster to the corresponding computer.
   */
  void transport(const std::map<std::string, std::string>& col_ip);

  /**
   * @note: after the transport, start a new client of the other cluster proxy,
   * sync the new data to the proxy.
   */
  void start_sync_client(const std::string& url, const std::string& path);
  void stop_sync_client(const std::string& url, const std::string& path);

  /**
   * @note: The new cluster which is transported by another should be start with
   * the copy_start function.
   */
  void copy_start(const std::vector<int>& col_num, const int& tot_files);

  void del(const std::set<Key>& keys);

  int execute_dump_wb();

  void backup(std::string& _return, const std::string& backup_type,
              const std::string& sub_dir,
              const std::map<std::string, std::string>& col_ip);
  void backup_start(std::string abs_snap_dir, int cf_count);
  std::string copy_data_from_backup(const std::vector<int>& col_num,
                                    const std::string& remote_dir) const;
  int print_database_info();

 private:
  void setRocksdbOpts(rocksdb::WriteOptions& writeOptions) {
    writeOptions.no_slowdown = true;
    writeOptions.low_pri = true;
    writeOptions.memtable_insert_hint_per_batch = true;
  }

  void insertWithUpdate(const std::string& key, const std::string& value) {
    TbbHashAccessor tbbHashAccessor;
    bool found = pCache_->find(tbbHashAccessor, key);
    if (found) {
      tbbHashAccessor->second = value;
    } else {
      pCache_->insert(std::make_pair(key, value));
    }
  }

  void insertWithUpdateUnit64(const Key& key, const std::string& value) {
    TbbUint64HashAccessor tbbUint64HashAccessor;
    bool found = pCacheSyncEmb_->find(tbbUint64HashAccessor, key);
    if (found) {
      tbbUint64HashAccessor->second = value;
    } else {
      pCacheSyncEmb_->insert(std::make_pair(key, value));
    }
  }

  static bool isAda(const std::string& option) {
    return (option == "adagrad" || option == "rmsp");
  }

  void putCache(const std::string& strFid, const std::string& strEmb,
                const std::string& option, const std::string& strAda,
                int updateTimes) {
    insertWithUpdate(strFid + "_emb", strEmb);
    if (isAda(option)) {
      insertWithUpdate(strFid + "_ada", strAda);
    }
    insertWithUpdate(strFid + "_update_times", std::to_string(updateTimes));
    insertWithUpdate(strFid + "_latest_time",
                     std::to_string(Timer::getNowInSecond()));
  }

  void putCacheWithoutAda(const std::string& strFid, const std::string& strEmb,
                          int updateTimes) {
    insertWithUpdate(strFid + "_emb", strEmb);
    insertWithUpdate(strFid + "_update_times", std::to_string(updateTimes));
    insertWithUpdate(strFid + "_latest_time",
                     std::to_string(Timer::getNowInSecond()));
  }

  bool getWithCache(rocksdb::ColumnFamilyHandle* cfHandle,
                    const std::string& strKey, std::string& value) {
    TbbHashConstAccessor hashConstAccessor;
    if (pCache_->find(hashConstAccessor, strKey)) {
      value = hashConstAccessor->second;
      return true;
    }
    if (swapFlag_) {
      if (pSwapCache_->find(hashConstAccessor, strKey)) {
        value = hashConstAccessor->second;
        return true;
      }
    }
    rocksdb::Status status =
        db->Get(rocksdb::ReadOptions(), cfHandle, strKey, &value);
    if (!status.ok()) {
      return false;
    }
    return true;
  }

  int getLen(const Key& key) {
    int slot = get_slot(key);
    auto meta_config = fea_use_length.find(slot);
    if (meta_config == fea_use_length.end()) {
      logger->info("slot {} is not configured", slot);
      return -1;
    }
    return meta_config->second;
  }

  // 对比找到的emb字符串长度是否与预定长度相等，不相等则新生成相等长度的字符串放到strEmb
  void setEmbWithLength(std::map<Key, std::string>& key_vals, const Key& key,
                        const std::string& oldEmbStr);

  // 根据update_times判断是否使用0填充emb，更新次数小采用0填充
  bool fillZeroByUpdateTimes(std::map<Key, std::string>& key_vals,
                             const Key& key, const TbbStringHashMap& cache);

  void batchDumpToDB();
  void batchSyncEmb();
  void syncEmb();

 private:
  TbbStringHashMap* pCache_ = nullptr;
  bool swapFlag_ = false;  // 初始时pSwapCache_不可用
  TbbStringHashMap* pSwapCache_ = nullptr;
  long lastSwapTime_;

  TbbUint64HashMap* pCacheSyncEmb_ = nullptr;
  TbbUint64HashMap* pSwapCacheSyncEmb_ = nullptr;
  long lastSwapTimeSyncEmb_;

  std::thread loopDumpThread;
  std::thread loopSyncEmbThread;
};
}  // namespace ps

#endif  // PARA_SERV_OP_H
