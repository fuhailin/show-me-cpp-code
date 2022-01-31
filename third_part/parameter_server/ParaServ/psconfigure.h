#ifndef PSCONFIGURE_H
#define PSCONFIGURE_H

#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "config.h"
#include "logger.hpp"
#include "nlohmann/json.hpp"
#include "tcmcp_HulkProxyServ.h"
using json = nlohmann::json;
using std::pair;
using std::string;
using std::to_string;

#ifndef OFFLINE_META_URL
#define OFFLINE_META_URL                                                    \
  "172.21.32.168:2181,172.21.32.136:2181,172.21.32.113:2181,172.21.32.116:" \
  "2181,172.21.32.196:2181"
#endif

#ifndef OFFLINE_META_PATH
#define OFFLINE_META_PATH \
  "/algorithm_research_center/group6/hulk_proxy/offlinemeta"
#endif

namespace ps {

class Configure : public BaseConfig {
 public:
  Configure() = default;
  int parse(int argc, char** argv);
  int help();
  bool get_db_conf();
  bool getmeta();
  bool getthriftport(int& port);
  void replacethriftport(int port);
  bool getmasterport();
  bool getslaveof();
  bool getmodelname(std::string& model_name);
  bool initdbname();
  bool getthreadnum(int& num);
  bool getjsonconfig(json** zook_info);
  bool getgroupid(std::string& groupId);
  bool get_machine_type(std::string& mt);
  bool getvalueof(const std::string& key, std::string& value);

  float ada_beta;
  float rmsp_beta;
  std::unordered_map<int, float> max_norm;
  std::unordered_map<int, float> learn_rate;
  std::unordered_map<int, std::string> optimazation;
  std::unordered_map<int, int> update_times;
  std::unordered_map<int, int> slot_dim;
  json meta;
  json nets;

  int ParseLine(std::vector<std::string>& argv) {
    return -1;  // 交给父类处理
  }

  int PrintUsage() { return -1; }

  int Version() { return 1; }

  static Configure* Instance() { return instance.get(); }

  static void SetInstance(std::shared_ptr<Configure> inst) { instance = inst; }

 private:
  std::shared_ptr<tcmcp_HulkProxyServClient> meta_client;
  std::unordered_map<std::string, std::string> options;
  void get_all_para();
  static std::shared_ptr<Configure> instance;
};

}  // namespace ps

#endif
