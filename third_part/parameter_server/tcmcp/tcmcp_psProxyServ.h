#ifndef _TCMCP_psProxyServ_H_
#define _TCMCP_psProxyServ_H_

#include "ThriftClientMultiConnectPlug.h"
#include "thrift/psProxyThrift/psProxyServ.h",
// diy include <other.h> if you need.

class tcmcp_psProxyServClient
    : public CThriftClinetMultiConnectPlug<psProxyServClient> {
 public:
  /*
   * constructor
   */
  tcmcp_psProxyServClient(const string zkHost, const string zkPath,
                          const int connectNumber,
                          const int timeout = 1000 * 10,
                          const double checkTimes = 1.0)
      : CThriftClinetMultiConnectPlug<psProxyServClient>(
            zkHost, zkPath, connectNumber, timeout, checkTimes) {}

 private:
  /*
   * virtual function.
   * create your thrift and insert into pool.
   */
  void createConnect(
      map<STR_ip_port_suffix, connectNode<psProxyServClient>>& pool,
      const string& ip, const int port);

 public:
  /*
   * tcmcp function list.
   */
  int tcmcp_push(const std::map<Key, std::string>& key_vals);

  int tcmcp_sync_push(const std::map<Key, std::string>& key_vals);

  int tcmcp_pushemb(const std::map<Key, std::string>& key_vals);

  int tcmcp_pushada(const std::map<Key, std::string>& key_vals);

  int tcmcp_pull(std::map<Key, std::string>& _return,
                 const std::set<Key>& keys);

  int tcmcp_pull_online(std::map<Key, std::string>& _return,
                        const std::set<Key>& keys);

  int tcmcp_replication(const std::string& zkUrl, const std::string& zkPath);

  int tcmcp_copy_data(const std::map<std::string, std::string>& fileNum_ip);

  int tcmcp_heartbeat(std::string& _return, const int32_t input);
};
#endif  //_TCMCP_psProxyServ_H_
