#include "psconfigure.h"

#include <climits>

#include "logger.h"

using namespace ps;
std::shared_ptr<Configure> Configure::instance;

int Configure::parse(int argc, char** argv) {
  std::string a(argv[1]);
  if (a == "-h" || a == "-help") {
    return help();
  }
  int j(1);
  while (j != argc) {
    std::string a(argv[j]);
    j++;
    if (a == "-n" || a == "-net") {
      std::string tmp(argv[j]);
      j++;
      // cout<<"haha"<<endl;
      options.insert(std::pair<std::string, std::string>("net", tmp));
      // cout<<options.at("net")<<endl;
    }
    if (a == "-m" || a == "-meta") {
      std::string tmp(argv[j]);
      j++;
      options.insert(std::pair<std::string, std::string>("meta", tmp));
    }
    if (a == "-d" || a == "-db") {
      std::string tmp(argv[j]);
      j++;
      options.insert(std::pair<std::string, std::string>("db", tmp));
    }

    if (a == "-tp" || a == "-thrift_port") {
      std::string tmp(argv[j]);
      j++;
      options.insert(std::pair<std::string, std::string>("thrift_port", tmp));
    }
    if (a == "-mp" || a == "-master_port") {
      std::string tmp(argv[j]);
      j++;
      options.insert(std::pair<std::string, std::string>("master_port", tmp));
    }
    if (a == "-sl" || a == "-slave_of") {
      std::string tmp(argv[j]);
      j++;
      options.insert(std::pair<std::string, std::string>("slave_of", tmp));
    }
    if (a == "-mn" || a == "-model_name") {
      std::string tmp(argv[j]);
      j++;
      options.insert(std::pair<std::string, std::string>("model_name", tmp));
    }
    if (a == "-thread_num") {
      std::string tmp(argv[j]);
      j++;
      // options.insert(std::pair<std::string, std::string>("thread_num", tmp));
    }
    if (a == "-exist_db") {
      std::string tmp(argv[j]);
      j++;
      options.insert(std::pair<std::string, std::string>("exist_db", tmp));
    }

    if (a == "-g" || a == "-groupid") {
      string tmp(argv[j]);
      j++;
      options.insert(pair<string, string>("groupid", tmp));
    }
    if (a == "-z" || a == "-zookeeper_info") {
      string tmp(argv[j]);
      j++;
      options.insert(pair<string, string>("zookeeper_info", tmp));
    }
    if (a == "-mt" || a == "-machine_type") {
      string tmp(argv[j]);
      j++;
      options.insert(pair<string, string>("machine_type", tmp));
    }
    if (a == "-r" || a == "-recover") {
      string tmp(argv[j]);
      j++;
      options.insert(pair<string, string>("recover", tmp));
    }
    if (a == "enable_update_times") {
      options.insert(
          std::pair<std::string, std::string>("enable_update_times", "true"));
    }
    if (a == "-cf") {
      // rocksdb cf count
      string tmp(argv[j]);
      j++;
      options.insert(pair<string, string>("cf", tmp));
    }
  }

  return 1;
}

int Configure::help() {
  std::cerr
      << "To launch this program, two files(conf/db.conf and "
         "conf/ps_zookeeper_info.json) are needed!"
      << std::endl
      << "Option -thread_num means the numbers of the thread used by thread "
         "server."
      << std::endl
      // <<"Option -n/-nets means the nets configure."<<std::endl
      // <<"Option -m/-meta means the meta configure."<<std::endl
      << "Option -mn/-model_name means the name of the model." << std::endl
      << "Option -mt/-machine_type means the type of this machine, three "
         "choices are available: offline, realtime and online."
      << std::endl
      // <<"Option -d/-db means the configure file for rocksdb."<<std::endl
      << "Option -tp/-thrift_port means the thrift port of this server, this "
         "used for workers communicate with this server"
      << std::endl
      << "Option -mp/-master_port means the master port of this server, this "
         "used for the slave communicate with this server"
      << std::endl
      << "Option -g/-groupid means the group id of this server, there at most "
         "two server using one id, one of which is a master and the other is a "
         "slave."
      << std::endl
      // <<"Option -z/-zookeeper_info means the information of zookeeper where
      // this server registed."<<std::endl
      << "Option -sl/-slave_of means the ip:port of the master server, if this "
         "one is a slave server."
      << std::endl
      << "The -sl/-slave_of option is needed if this is a slave server"
      << std::endl
      << "if -r/-recover is defined, database is going to recover from the "
         "option."
      << std::endl
      << "Option -ut/-enable_update_times stands for the use of _update_times."
      << std::endl;
  return -1;
}

bool Configure::get_machine_type(std::string& mt) {
  auto it = options.find("machine_type");
  if (it == options.end()) {
    return false;
  }
  mt = it->second;
  return true;
}

bool Configure::getjsonconfig(json** zook_info) {
  static json json_info;
  static bool has_read_config_file = false;

  if (!has_read_config_file) {
    std::ifstream infile;
    auto it = options.find("zookeeper_info");
    if (it == options.end()) {
      infile.open("./conf/ps_zookeeper_info.json");
    } else {
      infile.open(it->second);
    }
    if (!infile.is_open()) {
      logger->error("The zookeeper information file '{}' doesn't exist!!",
                    it->second.c_str());
      return false;
    }
    // json j;
    infile >> json_info;
    has_read_config_file = true;
    infile.close();
  }
  *zook_info = &json_info;
  return true;
}

bool Configure::get_db_conf() {
  std::string config;
  std::string filename;
  auto it = options.find("db");
  if (it == options.end()) {
    filename = "./conf/db.conf";
  } else {
    filename = it->second;
  }
  config.clear();

  char buf[4096];
  FILE* fp;
  if ((fp = fopen(filename.c_str(), "r")) == nullptr) {
    logger->error("Fatal error, can't open config file '{}'", it->second);
    return false;
  }
  while (fgets(buf, sizeof(buf), fp) != nullptr) {
    config.append(buf);
  }
  fclose(fp);

  if (loadConfigFromString(config) != 0) {
    return false;
  };

  return true;
}

bool Configure::getmeta() {
  auto it = options.find("meta");
  if (it == options.end()) {
    return false;
  }
  std::ifstream infile(it->second);
  if (!infile.is_open()) {
    logger->error("Fatal error, can't open the meta configure file '{}'",
                  it->second);
  }
  infile >> meta;
  // logger->info("meta file : {} ", meta);
  std::cout << meta << std::endl;
  get_all_para();
  return true;
}

bool Configure::getthriftport(int& port) {
  auto it = options.find("thrift_port");
  if (it == options.end()) {
    logger->error("The thrift_port has no value '{}'", 0);
    return false;
  }
  port = stoi(it->second);
  return true;
}

void Configure::replacethriftport(int port) {
  options["thrift_port"] = std::to_string(port);
}

bool Configure::getgroupid(std::string& groupId) {
  auto it = options.find("groupid");
  if (it == options.end()) {
    logger->error("The groupid has no value '{}'", 0);
    return false;
  }
  groupid = it->second;
  groupId = it->second;
  return true;
}

bool Configure::getmasterport() {
  auto it = options.find("master_port");
  if (it == options.end()) {
    logger->error("The master_port has no value '{}'", 0);
    return false;
  }
  master_port = stoi(it->second);
  return true;
}

bool Configure::getslaveof() {
  auto it = options.find("slave_of");
  if (it == options.end()) {
    mode = kModeMaster;
    return true;

  } else {
    mode = kModeSlave;
    std::string slaveof(it->second);
    std::stringstream ss(slaveof);
    std::string tmp;
    std::vector<std::string> vec_tmp;

    while (getline(ss, tmp, ':')) {
      vec_tmp.push_back(tmp);
    }
    if (vec_tmp.size() != 2) {
      logger->error("The slave_of has wrong value '{}'", 0);
      return false;
    }
    master.ip = vec_tmp.at(0);
    master.port = stoi(vec_tmp.at(1));
    // mode = kModeMaster;
    return true;
  }
}

bool Configure::initdbname() {
  auto it_mn = options.find("model_name");
  if (it_mn == options.end()) {
    logger->error("The model has no name! '{}'", 0);
    return false;
  }
  std::string model_name(it_mn->second);
  auto it_gid = options.find("groupid");
  if (it_gid == options.end()) {
    logger->error("The model has no name! '{}'", 0);
    return false;
  }
  std::string machine_type;
  get_machine_type(machine_type);

  std::string group_id(it_gid->second);
  std::string model_group;

  if (machine_type == "online") {
    model_group = model_name;
  } else {
    model_group = model_name + "_#" + group_id;
  }

  this->data_dir = this->data_dir + "/" + model_group;
  logger->info("current db dir is {} ", data_dir);
  return true;
}

bool Configure::getmodelname(std::string& model_name) {
  auto it = options.find("model_name");
  if (it == options.end()) {
    log_error("The model has no name! '%d'", 0);
    return false;
  }
  std::string tmp(it->second);
  model_name = tmp;

  return true;
}

void Configure::get_all_para() {
  if (meta["default"].find("ada_beta") == meta["default"].end()) {
    ada_beta = 0.1;
  } else {
    ada_beta = meta["default"].at("ada_beta");
  }
  if (meta["default"].find("rmsp_beta") == meta["default"].end()) {
    rmsp_beta = 0.9;
  } else {
    rmsp_beta = meta["default"].at("rmsp_beta");
  }
  float norm_default = 0;
  float rate_default = 0.01;
  std::string opti_default = "sgd";
  int up_time_default = 0;

  auto& default_fea = meta["default"];
  if (default_fea.find("max_norm") != default_fea.end()) {
    norm_default = default_fea["max_norm"];
  }
  if (default_fea.find("learn_rate") != default_fea.end()) {
    rate_default = default_fea["learn_rate"];
  }
  if (default_fea.find("optimazation") != default_fea.end()) {
    opti_default = default_fea["optimazation"];
  }
  if (default_fea.find("update_times") != default_fea.end()) {
    up_time_default = default_fea["update_times"];
  }

  for (auto& fea : meta.items()) {
    auto norm = norm_default;
    auto rate = rate_default;
    auto opti = opti_default;
    auto up_time = up_time_default;
    if (fea.key() == "default") {
      continue;
    } else {
      auto& fea_cont = fea.value();
      slot_dim.insert(std::make_pair(fea_cont["slot"], fea_cont["dim"]));
      if (fea_cont.find("max_norm") != fea_cont.end()) {
        norm = fea_cont["max_norm"];
      }
      if (fea_cont.find("learn_rate") != fea_cont.end()) {
        rate = fea_cont["learn_rate"];
      }
      if (fea_cont.find("optimazation") != fea_cont.end()) {
        opti = fea_cont["optimazation"];
      }
      if (fea_cont.find("update_times") != fea_cont.end()) {
        up_time = fea_cont["update_times"];
      }
      max_norm.insert(std::make_pair(fea_cont["slot"], norm));
      learn_rate.insert(std::make_pair(fea_cont["slot"], rate));
      optimazation.insert(std::make_pair(fea_cont["slot"], opti));
      update_times.insert(std::make_pair(fea_cont["slot"], up_time));
    }
  }
}

bool Configure::getthreadnum(int& num) {
  auto it = options.find("thread_num");
  if (it == options.end()) {
    log_error("The thread number should be put in '%d'", 0);
    return false;
  }
  num = stoi(it->second);
  return true;
}

bool Configure::getvalueof(const std::string& key, std::string& value) {
  auto kv = options.find(key);
  if (kv == options.end()) {
    // std::cout << "fail to load config of the key " << key << std::endl;
    return false;
  }
  value = kv->second;
  return true;
}
