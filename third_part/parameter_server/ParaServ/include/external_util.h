#ifndef EXTERNAL_UTIL_H
#define EXTERNAL_UTIL_H

#include "nlohmann/json.hpp"
using json = nlohmann::json;
#include <rocksdb/metadata.h>

#include "psconfigure.h"
#include "rocksdb/db.h"
/**
 * @note: The function used for the rocksdb transport
 */
json get_json_from_livemeta(const rocksdb::LiveFileMetaData& meta);
rocksdb::LiveFileMetaData get_livemeta_from_json(const json& j_meta);
json get_json_from_sstmeta(const rocksdb::ExportImportFilesMetaData& meta);
rocksdb::ExportImportFilesMetaData get_sstmeta_from_json(const json& j_meta);

/**
 * @note: The function used to start the main serv
 */

int parse_configure(ps::Configure* conf, int argc, char** argv);
int regist_zookeeper(ps::Configure* conf);

int start_server(ps::Configure* conf);

struct storage_tool {
  enum { STORAGE_NFS = 0, STORAGE_HDFS, STORAGE_REMOTEFS, STORAGE_OSS };
  static std::shared_ptr<storage_tool> inst_;
  static std::shared_ptr<storage_tool> Instance() { return inst_; }
  static void new_instance();
  static void new_instance(std::string type);
  storage_tool(ps::Configure* conf);
  // int put_datanode(const char* remote_url,const char* local_path);
  // int get_datanode(const char* remote_url,const char* local_path);
  virtual int remote_make_clear_dir(const char* dir);
  virtual int storage_tool_upload(const char* remote_dir,
                                  const char* column_family_name,
                                  const char* local_path);
  virtual int storage_tool_download(const char* remote_dir,
                                    const char* column_family_name,
                                    const char* local_path);
  std::string storage_type;
  std::string storage_path;
  std::string user_password;
};

struct oss_storage_tool : public storage_tool {
  oss_storage_tool(ps::Configure* conf);
  int remote_make_clear_dir(const char* dir);
  int storage_tool_upload(const char* remote_dir,
                          const char* column_family_name,
                          const char* local_path);
  int storage_tool_download(const char* remote_dir,
                            const char* column_family_name,
                            const char* local_path);
  std::string aliyun_secret;
  std::string aliyun_user;
  std::string aliyun_bucket;
};

#endif