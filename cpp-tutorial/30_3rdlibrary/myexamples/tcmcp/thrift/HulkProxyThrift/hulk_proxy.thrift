/*
 * @Author: xuejian
 * @Date: 2019-08-10 10:13:44
 */
include "scan_data.thrift"
namespace cpp hulk

service HulkProxyServ
{
    oneway void mpush(1: map<string, string> key_vals);
    oneway void push(1:string key, 2:string val);
    oneway void hmpush(1:string hash, 2: map<string, string> key_vals);
    oneway void mhmpush(1: map<string, map<string, string>> hkey_vals);
    oneway void hpush(1:string hash, 2:string key, 3:string value);
    string get(1: string key);
    string hget(1: string hash, 2: string key);
    map<string, string> mget(1: set<string> keys);
    map<string, map<string, string>> mhmget(1: map<string, set<string>> h_keys);
    map<string, string> hmget(1: string hash, 2: set<string> keys);
    map<string, string> hgetall(1: string hash);
    map<string, string> hgetall_limit(1: string hash, 2: i32 limit);
    scan_data.ScanData hscan(1: string hash, 2:string cursor, 3:i32 count);
    oneway void hdel(1:string hash, 2: string key);
    oneway void hmdel(1:string hash, 2: set<string> key);
    oneway void expire(1: i32 ttl);



}