#include "tcmcp_HulkProxyServ.h"

void tcmcp_HulkProxyServClient::createConnect(
    map<STR_ip_port_suffix, connectNode<hulk::HulkProxyServClient>>& pool,
    const string& ip, const int port) {
  CREATE_CONNECT_TFramedTransport_TBinaryProtocol(hulk::HulkProxyServClient);
}
/*
****************************************************
*****---tcmcp function list implementations.---*****
****************************************************
*/
int tcmcp_HulkProxyServClient::tcmcp_mpush(
    const std::map<std::string, std::string>& key_vals) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, mpush, (key_vals));
}
int tcmcp_HulkProxyServClient::tcmcp_push(const std::string& key,
                                          const std::string& val) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, push, (key, val));
}
int tcmcp_HulkProxyServClient::tcmcp_hmpush(
    const std::string& hash,
    const std::map<std::string, std::string>& key_vals) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hmpush, (hash, key_vals));
}
int tcmcp_HulkProxyServClient::tcmcp_mhmpush(
    const std::map<std::string, std::map<std::string, std::string>>&
        hkey_vals) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, mhmpush, (hkey_vals));
}
int tcmcp_HulkProxyServClient::tcmcp_hpush(const std::string& hash,
                                           const std::string& key,
                                           const std::string& value) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hpush, (hash, key, value));
}
int tcmcp_HulkProxyServClient::tcmcp_get(std::string& _return,
                                         const std::string& key) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, get, (_return, key));
}
int tcmcp_HulkProxyServClient::tcmcp_hget(std::string& _return,
                                          const std::string& hash,
                                          const std::string& key) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hget, (_return, hash, key));
}
int tcmcp_HulkProxyServClient::tcmcp_mget(
    std::map<std::string, std::string>& _return,
    const std::set<std::string>& keys) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, mget, (_return, keys));
}
int tcmcp_HulkProxyServClient::tcmcp_mhmget(
    std::map<std::string, std::map<std::string, std::string>>& _return,
    const std::map<std::string, std::set<std::string>>& h_keys) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, mhmget, (_return, h_keys));
}
int tcmcp_HulkProxyServClient::tcmcp_hmget(
    std::map<std::string, std::string>& _return, const std::string& hash,
    const std::set<std::string>& keys) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hmget, (_return, hash, keys));
}
int tcmcp_HulkProxyServClient::tcmcp_hgetall(
    std::map<std::string, std::string>& _return, const std::string& hash) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hgetall, (_return, hash));
}
int tcmcp_HulkProxyServClient::tcmcp_hgetall_limit(
    std::map<std::string, std::string>& _return, const std::string& hash,
    const int32_t limit) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hgetall_limit,
                    (_return, hash, limit));
}
int tcmcp_HulkProxyServClient::tcmcp_hscan(::hulk::ScanData& _return,
                                           const std::string& hash,
                                           const std::string& cursor,
                                           const int32_t count) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hscan,
                    (_return, hash, cursor, count));
}
int tcmcp_HulkProxyServClient::tcmcp_hdel(const std::string& hash,
                                          const std::string& key) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hdel, (hash, key));
}
int tcmcp_HulkProxyServClient::tcmcp_hmdel(const std::string& hash,
                                           const std::set<std::string>& key) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hmdel, (hash, key));
}
int tcmcp_HulkProxyServClient::tcmcp_hdel_all(const std::string& hash) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, hdel_all, (hash));
}
int tcmcp_HulkProxyServClient::tcmcp_expire(const int32_t ttl) {
  USE_tcmcp_NOT_POD(hulk::HulkProxyServClient, expire, (ttl));
}
