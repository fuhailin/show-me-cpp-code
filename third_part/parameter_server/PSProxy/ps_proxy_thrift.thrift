typedef i64 Key

service psProxyServ
{
    oneway void push(1: map<Key, string> key_vals),
    void sync_push(1: map<Key, string> key_vals),
    void pushemb(1: map<Key, string> key_vals),
    void pushada(1: map<Key, string> key_vals),
    map<Key, string> pull(1: set<Key> keys),
    map<Key, string> pull_online(1: set<Key> keys),
    map<Key, string> pull_online2(1: list<Key> keys),
    void replication(1:string zkUrl, 2:string zkPath),
    void stop_replication(1:string zkUrl, 2:string zkPath),
    void copy_data(1: map<string, string> fileNum_ip),
    string heartbeat(1:i32 input),
    string backup(1: string storage_type, 2:string backup_name),
    string change_sync_to(1: string zk_url,2:string zk_path),
    string status_cmd(1: string cmd, 2: list<string> values)
}
