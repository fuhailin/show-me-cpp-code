#include <iostream>

#include "external_util.h"
#include "para_serv_handler.h"
#include "parameter_server/common/logger.h"
#include "port_holder.h"

std::shared_ptr<spdlog::logger> logger;
const std::string loggerName = "ps_server_logger";

void initLogger(const std::string& loggerName, const std::string& logFileName) {
  spdlog::set_level(spdlog::level::info);
  spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%f] [thread %t] [%n] [%l] %v");
  // add a thread to flush log, use in multi-thread mode
  spdlog::flush_on(spdlog::level::info);
  spdlog::flush_every(std::chrono::seconds(1));  // flush every 1s
  // add a log thread
  logger = spdlog::daily_logger_mt<spdlog::async_factory>(loggerName,
                                                          logFileName, 0, 0);
}

void resourceHolder(int& fd) {
  auto conf = ps::Configure::Instance();
  int th_port = -1;
  if (!conf->getthriftport(th_port)) {
    std::cout << "Fatal error! The server port has no value!" << std::endl;
    return exit(5);
  }

  if (th_port == 0) {
    //选取随机的端口号作为服务端口
    getHoldRandomPort(fd, th_port);
    conf->replacethriftport(th_port);
  } else {
    fd = holdPort(th_port);
    if (fd < 0) {
      std::cout << "thrift port is used" << std::endl;
      std::cerr << "thrift port is used" << std::endl;
      exit(5);
    }
  }
}

void resourceHolderRelease(int fd) { close(fd); }

int main(int argc, char** argv) {
  ps::Configure::SetInstance(
      std::shared_ptr<ps::Configure>(new ps::Configure()));
  auto conf = ps::Configure::Instance();

  if (conf->parse(argc, argv) == -1) {
    return -1;
  }
  std::string groupId;
  conf->getgroupid(groupId);

  std::string model_name;
  if (!conf->getmodelname(model_name)) {
    std::cout << "Fatal error! The model name has no value!" << std::endl;
    return -1;
  }

  std::string logFileName = "/data/logs/ps_logs/";
  logFileName += model_name + "_" + groupId + "_server.log";
  initLogger(loggerName, logFileName);
  logger->info("ps server starting, loggerName: {}, logFileName: {}",
               loggerName, logFileName);
  logger->info("logFileName: {}", logFileName);

  // parse conf file
  if (parse_configure(conf, argc, argv) == -1) {
    logger->error("parse_configure error!");
    return -1;
  };
  storage_tool::new_instance("oss");

  int fd;
  resourceHolder(fd);
  resourceHolderRelease(fd);
  if (start_server(conf) == -1) {
    logger->error("start_server error!");
    return -1;
  };
  return 0;
}
