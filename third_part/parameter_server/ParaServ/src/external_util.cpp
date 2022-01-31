
#include "external_util.h"

#include <thrift/TToString.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/transport/TServerSocket.h>

#include <memory>
#include <thread>

#include "gproxy_server_register.h"
#include "para_serv_handler.h"
#include "parameter_server/ParaServ/prometheus_util.h"
#include "parameter_server/common/logger.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

json get_json_from_livemeta(const rocksdb::LiveFileMetaData& meta) {
  json re;
  re["column_family_name"] =
      meta.column_family_name;  // Name of the column family
  re["level"] = meta.level;     // Level at which this file resides.
  re["size"] = meta.size;
  // The name of the file.
  re["name"] = meta.name;
  // The full path where the file locates.
  re["db_path"] = meta.db_path;

  re["smallest_seqno"] =
      meta.smallest_seqno;  // Smallest sequence number in file.
  re["smallest_seqno"] =
      meta.largest_seqno;  // Largest sequence number in file.
  re["smallestkey"] =
      meta.smallestkey;                // Smallest user defined key in the file.
  re["largestkey"] = meta.largestkey;  // Largest user defined key in the file.
  re["num_reads_sampled"] =
      meta.num_reads_sampled;  // How many times the file is read.
  re["being_compacted"] =
      meta.being_compacted;  // true if the file is currently being compacted.

  re["num_entries"] = meta.num_entries;
  re["num_deletions"] = meta.num_deletions;

  return re;
}

rocksdb::LiveFileMetaData get_livemeta_from_json(const json& j_meta) {
  rocksdb::LiveFileMetaData meta;
  meta.column_family_name =
      j_meta["column_family_name"];  // Name of the column family
  meta.level = j_meta["level"];      // Level at which this file resides.
  meta.size = j_meta["size"];
  // The name of the file.
  meta.name = j_meta["name"];
  // The full path where the file locates.
  meta.db_path = j_meta["db_path"];

  meta.smallest_seqno =
      j_meta["smallest_seqno"];  // Smallest sequence number in file.
  meta.largest_seqno =
      j_meta["smallest_seqno"];  // Largest sequence number in file.
  meta.smallestkey =
      j_meta["smallestkey"];  // Smallest user defined key in the file.
  meta.largestkey =
      j_meta["largestkey"];  // Largest user defined key in the file.
  meta.num_reads_sampled =
      j_meta["num_reads_sampled"];  // How many times the file is read.
  meta.being_compacted =
      j_meta["being_compacted"];  // true if the file is currently being
                                  // compacted.

  meta.num_entries = j_meta["num_entries"];
  meta.num_deletions = j_meta["num_deletions"];
  logger->info("meta.column_family_name = {}", meta.column_family_name);
  logger->info("meta.name = {}", meta.name);
  logger->info("meta.db_path = {}", meta.db_path);
  logger->info("meta.level = {}", meta.level);
  logger->info("meta.size = ", meta.size);
  logger->info("------------------------------------------------------");

  return meta;
}

json get_json_from_sstmeta(const rocksdb::ExportImportFilesMetaData& meta) {
  json re;
  re["db_comparator_name"] = meta.db_comparator_name;
  for (auto& file : meta.files) {
    re["files"].push_back(get_json_from_livemeta(file));
  }
  if (meta.files.size() == 0) {
    logger->info("error: meta.files.size()==0");
    // exit(1);
  }
  return re;
}

rocksdb::ExportImportFilesMetaData get_sstmeta_from_json(const json& j_meta) {
  rocksdb::ExportImportFilesMetaData meta;
  meta.db_comparator_name = j_meta["db_comparator_name"];
  for (auto& file : j_meta["files"]) {
    meta.files.push_back(get_livemeta_from_json(file));
  }
  return meta;
}

int parse_configure(ps::Configure* conf, int argc, char** argv) {
  if (!conf->getmeta()) {
    // std::cout<<conf->meta<<std::endl;
    logger->error("Fatal error! the meta parse error! check file '{}", 0);
    return -1;
  }

  // this command must be ahead of the get model name;
  if (!conf->get_db_conf()) {
    logger->error("Fatal error! the thrift parse error! check file '{}", 0);
    return -1;
  }

  if (!conf->getmasterport()) {
    logger->error("Fatal error! The master port is missing '{}'", 0);
    return -1;
  }

  if (!conf->getslaveof()) {
    logger->error("Fatal error! The slave of has wrong form '{}'", 0);
    return -1;
  }
  if (!conf->initdbname()) {
    logger->error("Fatal error! The model name has no value '{}'", 0);
    return -1;
  }

  return 1;
}

int regist_zookeeper(ps::Configure* conf) {
  std::string model_name;
  if (!conf->getmodelname(model_name)) {
    logger->error("Fatal error! The model name has no value '{}'", 0);
    return -1;
  }
  json* zook_info;
  if (!conf->getjsonconfig(&zook_info)) {
    logger->error("Fatal error! There is no zookeeper information file '{}'",
                  0);
    return -1;
  }
  int port;
  if (!conf->getthriftport(port)) {
    logger->error("Fatal error! The thrift port is missing '{}'", 0);
    return -1;
  }
  const std::string server_zk_url = zook_info->at("zk_url");
  std::string server_zk_path = zook_info->at("zk_path");
  server_zk_path = server_zk_path + "/" + model_name;
  std::string mt;
  if (!conf->get_machine_type(mt)) {
    logger->error("Fatal error! There should be a machine type.");
    return -1;
  }
  if (mt == "offline") {
    server_zk_path += "_offline";
  } else if (mt == "realtime") {
    server_zk_path += "_realtime";
  } else if (mt == "online") {
    server_zk_path += "_online";
  } else {
    logger->info("The mathine type {} doesn't exist!!", mt);
    return -1;
  }

  std::string groupId;
  if (conf->getgroupid(groupId)) {
    logger->info("server_zk_url = {}", server_zk_url);
    logger->info("server_zk_path = {}", server_zk_path);
    gProxyServerRegister::serverRegiste2ZK(server_zk_url, server_zk_path, port,
                                           conf->groupid);
  }
  return 1;
}

int start_server(ps::Configure* conf) {
  int port;

  if (!conf->getthriftport(port)) {
    log_error("Fatal error! The thrift port is missing '%d'", 0);
    return -1;
  }

  uint32_t logicCPUNum = std::thread::hardware_concurrency();
  const int kThriftWorkerNum = 2 * logicCPUNum;
  logger->info("logicCPUNum: {}, kThriftWorkerNum: {}", logicCPUNum,
               kThriftWorkerNum);

  std::shared_ptr<ps::ParaServHandler> handler(new ps::ParaServHandler(conf));
  ps::ParaServHandler::setInstance(handler);

  std::string model;
  conf->getmodelname(model);
  prometheus_util::new_instance("10.0.25.56", "9091", model);
  auto ins = prometheus_util::Instance();
  ins->NewGauge("multi_pull_multi_get");
  ins->NewGauge("multi_pull_for_loop");
  ins->NewGauge("multi_pull_rocks_write");
  ins->NewGauge("multi_pull_all");
  ins->NewGauge("push_for_loop");
  ins->NewGauge("push_rocks_write");
  ins->NewGauge("pushemb_rocks_write");
  ins->NewGauge("pushada_rocks_write");
  ins->NewGauge("push_rocks_get");
  ins->NewGauge("push_all");
  ins->Register();

  std::shared_ptr<TProcessor> processor(new ps::ParaServProcessor(handler));
  std::shared_ptr<TNonblockingServerTransport> serverTransport(
      new TNonblockingServerSocket(port));
  std::shared_ptr<TTransportFactory> transportFactory(
      new TBufferedTransportFactory());
  std::shared_ptr<TProtocolFactory> protocolFactory(
      new TBinaryProtocolFactory());

  std::shared_ptr<ThreadManager> threadManager =
      ThreadManager::newSimpleThreadManager(kThriftWorkerNum);
  std::shared_ptr<PosixThreadFactory> threadFactory =
      std::shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  TNonblockingServer server(processor, protocolFactory, serverTransport,
                            threadManager);  // using pool of thread

  if (regist_zookeeper(conf) == -1) {
    return -1;
  };

  gProxyServerRegister::resetSigHandlers();

  server.serve();
  return 1;
}

std::shared_ptr<storage_tool> storage_tool::inst_;

void storage_tool::new_instance() {
  inst_.reset(new storage_tool(ps::Configure::Instance()));
}

void storage_tool::new_instance(std::string type) {
  if (type == "oss") {
    inst_.reset(new oss_storage_tool(ps::Configure::Instance()));
  } else {
    inst_.reset(new storage_tool(ps::Configure::Instance()));
  }
}

storage_tool::storage_tool(ps::Configure* conf) {
  // ps::Configure* conf = ps::Configure::Instance();
  json* json_config;
  if (!conf->getjsonconfig(&json_config)) {
    logger->error("Fatal error! There is no zookeeper information file '{}'",
                  0);
    exit(-2);
  }

  if (json_config->find("user_password") != json_config->end()) {
    user_password = json_config->at("user_password");
  }
  if (json_config->find("storage_type") != json_config->end()) {
    storage_type = json_config->at("storage_type");
  }
  if (json_config->find("storage_path") != json_config->end()) {
    storage_path = json_config->at("storage_path");
  }
}

int storage_tool::remote_make_clear_dir(const char* dir) {
  size_t n = storage_path.find(":");
  // std::cout <<  << std::endl;
  std::string ip = storage_path.substr(0, n);
  std::string path = storage_path.substr(n + 1);
  // auto scp_cmd = std::string("ssh -o StrictHostKeyChecking=no root@") + ip +
  // " mkdir -p " + path + "/" + dir; auto scp_cmd = std::string("sshpass -p ")
  // + user_password + " ssh -o StrictHostKeyChecking=no root@" + ip + " mkdir
  // -p " + path + "/" + dir;
  auto scp_cmd = std::string("ssh -o StrictHostKeyChecking=no root@") + ip +
                 " mkdir -p " + path + "/" + dir;
  logger->info("scp_cmd = {}", scp_cmd);
  int ret = system(scp_cmd.c_str());
  if (ret != 0) {
    logger->error("cmd exec failed");
  }
  return 0;
}

int storage_tool::storage_tool_upload(const char* remote_dir,
                                      const char* column_family_name,
                                      const char* local_path) {
  size_t n = storage_path.find(":");
  std::string ip = storage_path.substr(0, n);
  std::string path = storage_path.substr(n + 1);

  auto scp_cmd = std::string("scp -o StrictHostKeyChecking=no -r ") +
                 local_path + " root@" + storage_path + "/" + remote_dir;
  logger->info("scp_cmd = {}", scp_cmd);
  int ret = system(scp_cmd.c_str());
  if (ret != 0) {
    logger->error("cmd exec failed");
  }
  return 0;
}

int storage_tool::storage_tool_download(const char* remote_dir,
                                        const char* column_family_name,
                                        const char* local_path) {
  size_t n = storage_path.find(":");
  std::string ip = storage_path.substr(0, n);
  std::string path = storage_path.substr(n + 1);

  auto scp_cmd = std::string("scp -o StrictHostKeyChecking=no -r ") + "root@" +
                 ip + ":" + remote_dir + " " + local_path;
  logger->info("scp_cmd = {}", scp_cmd);
  int ret = system(scp_cmd.c_str());
  if (ret != 0) {
    logger->error("cmd exec failed");
  }
  return 0;
}

oss_storage_tool::oss_storage_tool(ps::Configure* conf) : storage_tool(conf) {
  logger->info("init oss");
}

int oss_storage_tool::storage_tool_upload(const char* remote_dir,
                                          const char* column_family_name,
                                          const char* local_path) {
  size_t n = storage_path.find(":");
  std::string ip = storage_path.substr(0, n);
  std::string path = storage_path.substr(n + 1);

  std::string rm_cmd = std::string("/usr/local/bin/ossutil64 rm -rf oss://") +
                       path + "/" + remote_dir + "/" + column_family_name + "/";
  system(rm_cmd.c_str());
  logger->info("rm oss, {}", rm_cmd);

  std::string upload = std::string("/usr/local/bin/ossutil64 cp -r ") +
                       local_path + "/ " + "oss://" + path + "/" + remote_dir +
                       "/" + column_family_name + "/";
  logger->info("upload oss, {}", upload);
  int ret = system(upload.c_str());
  if (ret != 0) {
    logger->error("cmd exec failed");
  }
  return ret;
}

int oss_storage_tool::storage_tool_download(const char* remote_dir,
                                            const char* column_family_name,
                                            const char* local_path) {
  size_t n = storage_path.find(":");
  std::string ip = storage_path.substr(0, n);
  std::string path = storage_path.substr(n + 1);
  std::string download =
      std::string("/usr/local/bin/ossutil64 cp --jobs 1 -r ") + "oss://" +
      path + "/" + remote_dir + "/ " + local_path + "/" + column_family_name +
      "/";
  logger->info("download oss, {}", download);
  int ret = system(download.c_str());
  if (ret != 0) {
    logger->error("cmd exec failed");
  }
  return ret;
}

int oss_storage_tool::remote_make_clear_dir(const char* dir) {
  size_t n = storage_path.find(":");
  std::string ip = storage_path.substr(0, n);
  std::string path = storage_path.substr(n + 1);
  // auto scp_cmd = std::string("/usr/local/bin/ossutil64 mkdir oss://") + path
  // + "/" + dir;
  auto scp_cmd = std::string("/usr/local/bin/ossutil64 rm -rf oss://") + path +
                 "/" + dir + "/";
  logger->info("scp_cmd: {}", scp_cmd);
  int ret = system(scp_cmd.c_str());
  logger->info("wait 5 seconds");
  sleep(5);
  return ret;
}
