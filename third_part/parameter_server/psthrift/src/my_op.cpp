#include "my_op.h"

#include <chrono>
#include <sstream>
#include <typeinfo>

#include "cityhash/src/city.h"
#include "rocksdb/write_batch.h"
using namespace ps;

// void MyOp::push(const std::vector<Key> & keys, const
// std::vector<vector<double>> & Vals)
void MyOp::push(const std::map<Key, std::string>& key_vals, bool is_sync) {
  rocksdb::WriteBatch batch;

  for (auto it = key_vals.begin(); it != key_vals.end(); ++it) {
    int slot(get_slot(it->first));
    // std::string fea_name(std::to_string(slot));

    // json& meta = conf->meta;
    float max_norm, learn;  //, ada_beta;
    std::string opti_;
    //============get the parameter from conf============
    // std::cout<<"before at"<<std::endl<<slot<<std::endl;;
    max_norm = conf->max_norm.at(slot);
    learn = conf->learn_rate.at(slot);
    opti_ = conf->optimazation.at(slot);
    // std::cout<<"end at"<<std::endl;

    // float learn = learn_rate.at(keyind);
    const Key& fid = it->first;
    std::vector<float> vec_grad(str2vec(it->second));
    const size_t& val_size = vec_grad.size();
    Map<MatrixXf> grad(&vec_grad.at(0), 1, vec_grad.size());

    // std::cout<<"The grad mean "<<grad.mean()<<std::endl;

    std::string values;
    MatrixXf ada_sum;  //(MatrixXf::Constant(1, val_size, ada_beta));
    rocksdb::Status status;
    if (opti_ == "adagrad" || opti_ == "rmsp") {
      status = db->Get(rocksdb::ReadOptions(), cfHandles.at("ada"),
                       std::to_string(fid), &values);
      assert(status.ok());

      std::vector<float> tmp(str2vec(values));
      ada_sum = Map<MatrixXf>(&tmp.at(0), 1, tmp.size());
    }

    status = db->Get(rocksdb::ReadOptions(), cfHandles.at("emb"),
                     std::to_string(fid), &values);
    assert(status.ok());
    std::vector<float> tmp2(str2vec(values));

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
    // std::cout<<ada_sum.mean()<<std::endl;
    // the maxnarm of embedding
    if (max_norm > 1E-6) {
      l2_norm_vec(para_dict, max_norm);
    }
    // std::cout<<"++++++++++the
    // emb+++++++++++"<<std::endl<<para_dict<<std::endl;

    int64_t latest_time =
        (int64_t)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();

    status = db->Get(rocksdb::ReadOptions(), cfHandles.at("update_times"),
                     std::to_string(fid), &values);
    int up_tmp(stoi(values));
    up_tmp += 1;

    batch.Put(cfHandles.at("emb"), std::to_string(fid), vec2str(para_dict));
    if (opti_ == "adagrad" || opti_ == "rmsp") {
      batch.Put(cfHandles.at("ada"), std::to_string(fid), vec2str(ada_sum));
    }
    batch.Put(cfHandles.at("update_times"), std::to_string(fid),
              std::to_string(up_tmp));
    batch.Put(cfHandles.at("latest_time"), std::to_string(fid),
              std::to_string(latest_time));
  }
  // exit(true);
  if (batch.Count()) {
    rocksdb::WriteOptions write_options;
    //========for the sync write===========
    if (is_sync) {
      write_options.sync = true;
    }
    //=====================================
    // std::cout<<"==========before
    // write==========="<<std::endl<<log_Time()<<std::endl;
    db->Write(write_options, &batch);
    // std::cout<<log_Time()<<std::endl<<"==============end
    // write============"<<std::endl;

    rep_b->notify_replication();
  }
}

// void MyOp::pushemb(const std::vector<Key> & keys, const
// std::vector<vector<double>> & Vals)
void MyOp::pushemb(const std::map<Key, std::string>& key_vals) {
  rocksdb::WriteBatch batch;

  for (auto it = key_vals.begin(); it != key_vals.end(); ++it) {
    auto& fid = it->first;
    batch.Put(cfHandles.at("emb"), std::to_string(fid), it->second);
    batch.Put(cfHandles.at("update_times"), std::to_string(fid), "0");
  }

  // std::cout<<batch.Count()<<std::endl;
  if (batch.Count()) {
    rocksdb::WriteOptions write_options;
    db->Write(write_options, &batch);
    rep_b->notify_replication();
  }
}

void MyOp::pushada(const std::map<Key, std::string>& key_vals) {
  rocksdb::WriteBatch batch;

  for (auto it = key_vals.begin(); it != key_vals.end(); ++it) {
    auto& fid = it->first;
    batch.Put(cfHandles.at("ada"), std::to_string(fid), it->second);
  }

  if (batch.Count()) {
    rocksdb::WriteOptions write_options;
    db->Write(write_options, &batch);
    rep_b->notify_replication();
  }
}

// void MyOp::pull(const std::vector<Key> & keys, std::vector<std::string> &
// Vals)
void MyOp::pull(std::map<Key, std::string>& key_vals,
                const std::set<Key>& keys) {
  // std::cout<<"start pull"<<std::endl;
  // Vals.resize(n);
  rocksdb::WriteBatch batch;
  // cout<<log_Time()<<endl;
  // for(size_t i(0); i<n; ++i)
  // {

  for (auto key : keys) {
    int keyind(get_slot(key));
    int& slot = keyind;

    std::string values;
    // string tmp()
    rocksdb::Status state = db->Get(rocksdb::ReadOptions(), cfHandles.at("emb"),
                                    std::to_string(key), &values);

    // cout<<values<<endl;
    if (state.IsNotFound()) {
      // std::cout<<get_slot(key)<<std::endl;
      std::string fea_name(std::to_string(keyind));

      // json& meta = conf->meta;
      float max_norm, ada_beta;
      std::string opti_;
      //=======get the parameter form conf==========
      // std::cout<<slot<<std::endl;
      int _length;
      try {
        max_norm = conf->max_norm.at(slot);
        // std::cout<<ada_beta<<std::endl;
        opti_ = conf->optimazation.at(slot);

        _length = fea_use_length.at(keyind);
      } catch (...) {
        std::cout << "The slot " << slot << "has no feature in the meta file"
                  << std::endl;
        assert(false);
      }

      ada_beta = conf->ada_beta;

      //==========the norm distribution and clip one===========
      // MatrixXf tmp(MatrixRandNorm(0, 1./sqrt(_length), 1, _length));
      // clip(tmp, -2/sqrt(_length), 2/sqrt(_length));
      //=======================================================
      //=================the truncated_norm ones===============
      MatrixXf tmp(Truncated_MatrixRandNorm(0, 1. / sqrt(_length), 1, _length));
      //=======================================================
      // std::cout<<"slot:"<<slot<<std::endl<<tmp.cwiseAbs().sum()<<std::endl<<"======"<<std::endl;

      l2_norm_vec(tmp, max_norm);

      std::string str_tmp = vec2str(tmp);
      key_vals.insert(std::make_pair(key, str_tmp));

      int64_t latest_time =
          (int64_t)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();

      batch.Put(cfHandles.at("emb"), std::to_string(key), str_tmp);
      if (opti_ == "adagrad" || opti_ == "rmsp") {
        batch.Put(cfHandles.at("ada"), std::to_string(key),
                  vec2str(MatrixXf::Constant(1, _length, ada_beta)));
      }
      batch.Put(cfHandles.at("latest_time"), std::to_string(key),
                std::to_string(latest_time));
      batch.Put(cfHandles.at("update_times"), std::to_string(key), "0");
    } else {
      key_vals.insert(std::make_pair(key, values));
    }
  }

  if (batch.Count()) {
    rocksdb::WriteOptions write_options;
    //========for the sync write===========
    write_options.sync = true;
    write_options.low_pri = true;
    //=====================================

    db->Write(write_options, &batch);
    rep_b->notify_replication();
  }
  // std::cout<<"end pull"<<std::endl;
}

void MyOp::multi_pull(std::map<Key, std::string>& key_vals,
                      const std::set<Key>& keys) {
  rocksdb::WriteBatch batch;

  std::vector<rocksdb::Slice> slices;
  std::vector<std::string> keys_str;
  std::vector<rocksdb::ColumnFamilyHandle*> tmp_handle;

  double start, end;

  start = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();
  for (auto s : keys) {
    keys_str.push_back(std::to_string(s));
    slices.push_back(rocksdb::Slice(keys_str.at(keys_str.size() - 1)));
    tmp_handle.push_back(cfHandles.at("emb"));
  }
  end = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  if (end - start > 0.5)
    std::cout << "The first loop takes " << end - start << "s" << std::endl;

  // std::cout<<tmp_handle.size()<<std::endl;
  std::vector<std::string> values;
  start = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();
  std::vector<rocksdb::Status> status =
      db->MultiGet(rocksdb::ReadOptions(), tmp_handle, slices, &values);
  end = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  if (end - start > 0.5)
    std::cout << "The multiget takes " << end - start << "s" << std::endl;
  // std::cout<<"haha"<<std::endl;

  start = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();
  for (size_t i(0); i < status.size(); ++i) {
    if (status.at(i).IsNotFound()) {
      int keyind = get_slot(std::stoll(keys_str.at(i)));
      int& slot = keyind;
      std::string fea_name(std::to_string(keyind));

      // json& meta = conf->meta;
      float max_norm, ada_beta;
      std::string opti_;
      int _length;
      //=======get the parameter form conf==========
      // std::cout<<slot<<std::endl;
      try {
        max_norm = conf->max_norm.at(slot);
        // std::cout<<ada_beta<<std::endl;
        opti_ = conf->optimazation.at(slot);
        _length = fea_use_length.at(keyind);
      } catch (...) {
        std::cout << "The slot " << slot << "has no feature in the meta file"
                  << std::endl;
        assert(false);
      }

      ada_beta = conf->ada_beta;

      //==========the norm distribution and clip one===========
      // MatrixXf tmp(MatrixRandNorm(0, 1./sqrt(_length), 1, _length));
      // clip(tmp, -2/sqrt(_length), 2/sqrt(_length));
      //=======================================================
      //=================the truncated_norm ones===============
      MatrixXf tmp(Truncated_MatrixRandNorm(0, 1. / sqrt(_length), 1, _length));
      //=======================================================
      // std::cout<<"slot:"<<slot<<std::endl<<tmp.cwiseAbs().sum()<<std::endl<<"======"<<std::endl;

      l2_norm_vec(tmp, max_norm);

      std::string str_tmp = vec2str(tmp);
      key_vals.insert(std::make_pair(std::stoll(keys_str.at(i)), str_tmp));

      int64_t latest_time =
          (int64_t)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();

      batch.Put(cfHandles.at("emb"), keys_str.at(i), vec2str(tmp));
      if (opti_ == "adagrad" || opti_ == "rmsp") {
        batch.Put(cfHandles.at("ada"), keys_str.at(i),
                  vec2str(MatrixXf::Constant(1, _length, ada_beta)));
      }
      batch.Put(cfHandles.at("latest_time"), keys_str.at(i),
                std::to_string(latest_time));
      batch.Put(cfHandles.at("update_times"), keys_str.at(i), "0");

    } else {
      key_vals.insert(std::make_pair(std::stoll(keys_str.at(i)), values.at(i)));
    }
  }
  end = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  if (end - start > 0.5)
    std::cout << "The second loop takes " << end - start << "s" << std::endl;

  start = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();
  if (batch.Count()) {
    rocksdb::WriteOptions write_options;
    //========for the sync write===========
    write_options.sync = false;
    //=====================================

    db->Write(write_options, &batch);
    rep_b->notify_replication();
  }
  end = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  if (end - start > 0.5)
    std::cout << "The write takes " << end - start << "s" << std::endl;
}

// void MyOp::pull_online(const std::vector<Key> & keys,
// std::vector<std::string> & Vals)
void MyOp::pull_online(std::map<Key, std::string>& key_vals,
                       const std::set<Key>& keys) {
  std::vector<rocksdb::Slice> slices;
  std::vector<std::string> keys_str;
  std::vector<rocksdb::ColumnFamilyHandle*> emb_handle, update_handle;

  double start, end;

  start = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();
  for (auto s : keys) {
    keys_str.push_back(std::to_string(s));
    slices.push_back(rocksdb::Slice(keys_str.at(keys_str.size() - 1)));
    emb_handle.push_back(cfHandles.at("emb"));
    update_handle.push_back(cfHandles.at("update_times"));
  }
  end = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  if (end - start > 0.5)
    std::cout << "The first loop takes " << end - start << "s" << std::endl;

  // std::cout<<tmp_handle.size()<<std::endl;
  std::vector<std::string> values_emb;
  std::vector<std::string> values_update;
  start = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();
  std::vector<rocksdb::Status> status_emb =
      db->MultiGet(rocksdb::ReadOptions(), emb_handle, slices, &values_emb);
  std::vector<rocksdb::Status> status_update = db->MultiGet(
      rocksdb::ReadOptions(), update_handle, slices, &values_update);
  end = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  if (end - start > 0.5)
    std::cout << "The multiget takes " << end - start << "s" << std::endl;
  // std::cout<<"haha"<<std::endl;

  start = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
              std::chrono::system_clock::now().time_since_epoch())
              .count();
  for (size_t i(0); i < status_emb.size(); ++i) {
    if (status_emb.at(i).IsNotFound()) {
      int keyind = get_slot(std::stoll(keys_str.at(i)));

      int& _length = fea_use_length.at(keyind);

      //==========the norm distribution and clip one===========
      // MatrixXf tmp(MatrixRandNorm(0, 1./sqrt(_length), 1, _length));
      // clip(tmp, -2/sqrt(_length), 2/sqrt(_length));
      //=======================================================
      //=================the truncated_norm ones===============
      MatrixXf tmp(MatrixXf::Zero(1, _length));
      //=======================================================
      // std::cout<<"slot:"<<slot<<std::endl<<tmp.cwiseAbs().sum()<<std::endl<<"======"<<std::endl;

      std::string str_tmp = vec2str(tmp);
      key_vals.insert(std::make_pair(std::stoll(keys_str.at(i)), str_tmp));

    } else {
      int slot = get_slot(std::stoll(keys_str.at(i)));
      int update_times_real = std::stoi(values_update.at(i));
      int update_std = conf->update_times.at(slot);
      if (update_times_real > update_std) {
        key_vals.insert(
            std::make_pair(std::stoll(keys_str.at(i)), values_emb.at(i)));
      } else {
        int& _length = fea_use_length.at(slot);
        MatrixXf tmp = MatrixXf::Zero(1, _length);
        key_vals.insert(
            std::make_pair(std::stoll(keys_str.at(i)), vec2str(tmp)));
      }
    }
  }
  end = (double)std::chrono::duration_cast<std::chrono::duration<double>>(
            std::chrono::system_clock::now().time_since_epoch())
            .count();
  if (end - start > 0.5)
    std::cout << "The second loop takes " << end - start << "s" << std::endl;
}
