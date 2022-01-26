/*
 * @Description: In User Settings Edit
 * @Author: xuejian
 * @Date: 2019-08-10 10:13:44
 * @LastEditTime: 2019-11-19 10:04:08
 * @LastEditors: Please set LastEditors
 */

typedef i64 Key



service Serv
{

    // void push(1: list<Key> keys, 2: list<list<double>> Vals),
    oneway void push(1: map<Key, string> key_vals),
    void sync_push(1: map<Key, string> key_vals),
    void pushemb(1: map<Key, string> key_vals),
    void pushada(1: map<Key, string> key_vals),
    map<Key, string> pull(1: set<Key> keys),
    map<Key, string> pull_online(1: set<Key> keys),
    string heartbeat(1: i32 beat),

}