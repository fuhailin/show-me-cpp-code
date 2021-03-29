typedef i64 Key


service psProxyServ
{
    oneway void push(1: map<Key, string> key_vals),
    void sync_push(1: map<Key, string> key_vals),
    void pushemb(1: map<Key, string> key_vals),
    void pushada(1: map<Key, string> key_vals),
    map<Key, string> pull(1: set<Key> keys),
    map<Key, string> pull_online(1: set<Key> keys),
    void replication(1:string zkUrl, 2:string zkPath),
    void copy_data(1: map<string, string> fileNum_ip),
    string heartbeat(1:i32 input)
}