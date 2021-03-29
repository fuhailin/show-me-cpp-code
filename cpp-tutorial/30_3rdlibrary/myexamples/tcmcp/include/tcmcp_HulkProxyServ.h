/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2020-01-17 16:09:25
 */
#ifndef _TCMCP_HulkProxyServ_H_
#define _TCMCP_HulkProxyServ_H_

#include "ThriftClientMultiConnectPlug.h"
#include "HulkProxyServ.h"
// diy include <other.h> if you need.


class tcmcp_HulkProxyServClient:public CThriftClinetMultiConnectPlug<hulk::HulkProxyServClient>
{

public:
    /*
    * constructor
    */
    tcmcp_HulkProxyServClient(const string zkHost, const string zkPath, const int connectNumber, const int timeout=1000*10, const double checkTimes=1.0):
                    CThriftClinetMultiConnectPlug<hulk::HulkProxyServClient>(zkHost, zkPath, connectNumber, timeout, checkTimes){}

private:
    /*
    * virtual function.
    * create your thrift and insert into pool.
    */
    void createConnect(map<STR_ip_port_suffix, connectNode<hulk::HulkProxyServClient>>& pool, const string& ip, const int port);

public:
    /*
    * tcmcp function list.
    */
    int tcmcp_mpush(const std::map<std::string, std::string> & key_vals);

    int tcmcp_push(const std::string& key, const std::string& val);

    int tcmcp_hmpush(const std::string& hash, const std::map<std::string, std::string> & key_vals);

    int tcmcp_mhmpush(const std::map<std::string, std::map<std::string, std::string> > & hkey_vals);

    int tcmcp_hpush(const std::string& hash, const std::string& key, const std::string& value);

    int tcmcp_get(std::string& _return, const std::string& key);

    int tcmcp_hget(std::string& _return, const std::string& hash, const std::string& key);

    int tcmcp_mget(std::map<std::string, std::string> & _return, const std::set<std::string> & keys);

    int tcmcp_mhmget(std::map<std::string, std::map<std::string, std::string> > & _return, const std::map<std::string, std::set<std::string> > & h_keys);

    int tcmcp_hmget(std::map<std::string, std::string> & _return, const std::string& hash, const std::set<std::string> & keys);

    int tcmcp_hgetall(std::map<std::string, std::string> & _return, const std::string& hash);

    int tcmcp_hgetall_limit(std::map<std::string, std::string> & _return, const std::string& hash, const int32_t limit);

    int tcmcp_hscan( ::hulk::ScanData& _return, const std::string& hash, const std::string& cursor, const int32_t count);

    int tcmcp_hdel(const std::string& hash, const std::string& key);

    int tcmcp_hdel_all(const std::string& hash);

    int tcmcp_hmdel(const std::string& hash, const std::set<std::string> & key);

    int tcmcp_expire(const int32_t ttl);


};
#endif //_TCMCP_HulkProxyServ_H_

