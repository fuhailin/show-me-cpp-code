#include "tcmcp_psProxyServ.h"

void tcmcp_psProxyServClient::createConnect(
    map<STR_ip_port_suffix, connectNode<psProxyServClient>>& pool,
    const string& ip, const int port) {
  CREATE_CONNECT_TFramedTransport_TBinaryProtocol(psProxyServClient);
}
/*
****************************************************
*****---tcmcp function list implementations.---*****
****************************************************
*/
int tcmcp_psProxyServClient::tcmcp_push(
    const std::map<Key, std::string>& key_vals) {
  USE_tcmcp_NOT_POD(psProxyServClient, push, (key_vals));
}
int tcmcp_psProxyServClient::tcmcp_sync_push(
    const std::map<Key, std::string>& key_vals) {
  USE_tcmcp_NOT_POD(psProxyServClient, sync_push, (key_vals));
}
int tcmcp_psProxyServClient::tcmcp_pushemb(
    const std::map<Key, std::string>& key_vals) {
  USE_tcmcp_NOT_POD(psProxyServClient, pushemb, (key_vals));
}
int tcmcp_psProxyServClient::tcmcp_pushada(
    const std::map<Key, std::string>& key_vals) {
  USE_tcmcp_NOT_POD(psProxyServClient, pushada, (key_vals));
}
int tcmcp_psProxyServClient::tcmcp_pull(std::map<Key, std::string>& _return,
                                        const std::set<Key>& keys) {
  USE_tcmcp_NOT_POD(psProxyServClient, pull, (_return, keys));
}
int tcmcp_psProxyServClient::tcmcp_pull_online(
    std::map<Key, std::string>& _return, const std::set<Key>& keys) {
  USE_tcmcp_NOT_POD(psProxyServClient, pull_online, (_return, keys));
}
int tcmcp_psProxyServClient::tcmcp_replication(const std::string& zkUrl,
                                               const std::string& zkPath) {
  USE_tcmcp_NOT_POD(psProxyServClient, replication, (zkUrl, zkPath));
}
int tcmcp_psProxyServClient::tcmcp_copy_data(
    const std::map<std::string, std::string>& fileNum_ip) {
  USE_tcmcp_NOT_POD(psProxyServClient, copy_data, (fileNum_ip));
}
int tcmcp_psProxyServClient::tcmcp_heartbeat(std::string& _return,
                                             const int32_t input) {
  USE_tcmcp_NOT_POD(psProxyServClient, heartbeat, (_return, input));
}
