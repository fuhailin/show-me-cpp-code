#ifndef CACHE_H
#define CACHE_H

#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include "tbb/concurrent_hash_map.h"
#include "tbb/concurrent_queue.h"
#include "time.h"

template <class key_T, class val_T>
class Cache {
 private:
  struct Value {
    key_T key;
    val_T value;
    uint64_t create_time;
  };
  typedef tbb::concurrent_hash_map<key_T, std::shared_ptr<Value>> HashMap;
  typedef tbb::concurrent_queue<std::shared_ptr<Value>> ConQueue;
  typedef typename HashMap::const_accessor HashMapConstAccessor;
  // typedef typename HashMap::accessor HashMapAccessor;
  // typedef typename HashMap::iterator HashMapIterator;
  typedef typename HashMap::value_type HashMapValuePair;
  uint64_t expire_time_;
  HashMap data_map_;
  ConQueue data_queue_;
  bool flag_;
  std::thread loop_thread;

 public:
  Cache(uint64_t expire_time) : expire_time_(expire_time) {
    flag_ = true;
    loop_thread = std::thread(&Cache::loop_check, this);
  };
  ~Cache() {
    flag_ = false;
    loop_thread.join();
  };

  void loop_check() {
    while (true) {
      std::shared_ptr<Value> tmp_value;
      bool res = data_queue_.try_pop(tmp_value);
      if (!res) {
        if (!flag_) {
          std::cout << "kill thread" << std::endl;
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        continue;
      }
      auto live_time = time(NULL) - tmp_value->create_time;
      if (live_time < expire_time_) {
        std::cout << "wait time = " << 1000 * (expire_time_ - live_time)
                  << std::endl;
        std::cout << "data_map_.size = " << data_map_.size()
                  << ", data_queue_.size = " << data_queue_.unsafe_size()
                  << std::endl;
        std::this_thread::sleep_for(
            std::chrono::milliseconds(1000 * (expire_time_ - live_time)));
      }
      HashMapConstAccessor hash_accessor;
      if (data_map_.find(hash_accessor, tmp_value->key)) {
        auto& tmp_struct = hash_accessor->second;
        if ((time(NULL) - tmp_struct->create_time) >= expire_time_) {
          data_map_.erase(hash_accessor);
          // std::cout<<"erase key: "<<tmp_value->key<<std::endl;
        }
      }
      if (!flag_) {
        std::cout << "kill thread" << std::endl;
        break;
      }
    }
  };

  void add(key_T key, val_T value) {
    auto val_ptr = std::make_shared<Value>();
    val_ptr->value = value;
    val_ptr->key = key;
    val_ptr->create_time = time(NULL);
    HashMapValuePair map_value_pair(key, val_ptr);
    data_map_.insert(map_value_pair);
    data_queue_.push(val_ptr);
  };
  int get(key_T& key, val_T& value) {
    HashMapConstAccessor hash_accessor;
    if (data_map_.find(hash_accessor, key)) {
      auto& tmp_struct = hash_accessor->second;
      if ((time(NULL) - tmp_struct->create_time) < expire_time_) {
        value = tmp_struct->value;
        return 1;
      }
    }
    return 0;
  };
};

#endif