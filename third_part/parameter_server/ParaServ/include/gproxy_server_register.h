#ifndef _GPROXY_SERVER_REGISTER_H_
#define _GPROXY_SERVER_REGISTER_H_
#include <arpa/inet.h> /* inet_ntop */
#include <netdb.h>     /* struct hostent */
#include <stdio.h>
#include <unistd.h>/* gethostname */

#include <string>
#include <vector>

#include "nlohmann/json.hpp"
#include "parameter_server/common/logger.h"
#include "zkclient.h"

namespace gProxyServerRegister {
static std::string RegPath;

using json = nlohmann::json;
std::string getIp() {
  char name[256];
  gethostname(name, sizeof(name));
  struct hostent* host = gethostbyname(name);
  char szBuf[16];
  const char* ret =
      inet_ntop(host->h_addrtype, host->h_addr_list[0], szBuf, sizeof(szBuf));
  if (nullptr == ret) {
    return "";
  }
  return szBuf;
}

void unregisterFromZK(int signal) {
  ZKClient& zkclient = ZKClient::GetInstance();
  zkclient.Delete(RegPath);
  logger->info("on signal {}, {} is deleted from zk", signal, RegPath);
  exit(signal);
}

void resetSigHandlers() {
  signal(SIGKILL, unregisterFromZK);
  signal(SIGTERM, unregisterFromZK);
  signal(SIGHUP, unregisterFromZK);
  signal(SIGSTOP, unregisterFromZK);
  signal(SIGTSTP, unregisterFromZK);
  signal(SIGINT, unregisterFromZK);
}

int serverRegiste2ZK(const std::string& zkUrl, const std::string& zkPath,
                     const int iThriftPort, const string& groupid,
                     const int zkTimeout = 10000) {
  // 连接zk
  ZKClient& zkclient = ZKClient::GetInstance();
  if (!zkclient.Init(zkUrl, zkTimeout)) {
    logger->error("ZKClient failed to init...");
    return -1;
  }
  zkclient.Create(zkPath, zkPath, ZOO_PERSISTENT);
  std::string groupPath = zkPath + "/" + groupid;
  std::string strServerNumber;  // 获取节点编号
  std::string&& ip = getIp();   // 获取本机ip
  logger->info("{}", ip);
  if (ip.empty()) {
    return -1;
  }

  // 获取子节点
  std::vector<std::string> vecGroupid;
  zkclient.GetChildren(zkPath, &vecGroupid);
  if (std::find(vecGroupid.begin(), vecGroupid.end(), groupid) !=
      vecGroupid.end()) {
    std::vector<std::string> vecRocksdbNode;
    zkclient.GetChildren(groupPath, &vecRocksdbNode);

    // 主从节点全部在线，不能注册2个以上
    if (vecRocksdbNode.size() >= 2) {
      logger->info(
          "==============主从节点全部在线,不能注册2个以上=============");
      logger->info(
          "=====若坚持上线，请关闭本进程，稍后重试或手动删除zk上的节点====");
      return -1;
    }
    if (vecRocksdbNode.size() == 0) {
      strServerNumber = "0";
    } else {
      strServerNumber = to_string(std::stoi(vecRocksdbNode[0]) + 1);
    }
  } else {
    // 创建rocksdb组，持久节点
    if (zkclient.Create(groupPath, groupid, ZOO_PERSISTENT)) {
      return -1;
    }
    strServerNumber = "0";
  }

  json j;
  j["ip"] = ip;
  j["port"] = iThriftPort;
  // 创立临时节点
  std::string nodePath = groupPath + "/" + strServerNumber;
  if (zkclient.Create(nodePath, j.dump(), ZOO_EPHEMERAL)) {
    return -1;
  } else {
    logger->info("[SUCCESS] ---- ZKClient Create ----");
    RegPath = nodePath;
  }
  return 0;
}

};  // namespace gProxyServerRegister

#endif  // _GPROXY_SERVER_REGISTER_H_
