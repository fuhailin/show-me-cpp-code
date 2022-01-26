namespace cpp ps
typedef i64 Key

service ParaServ
{

    oneway void push(1: map<Key, string> key_vals),
    void sync_push(1: map<Key, string> key_vals),
    void pushemb(1: map<Key, string> key_vals),
    void pushada(1: map<Key, string> key_vals),
    map<Key, string> pull(1: set<Key> keys),
    map<Key, string> pull_online(1: set<Key> keys),
    void start(1:list<i32> col_num, 2: i32 tot_files),
    void copy_start(1:list<i32> col_num, 2: i32 tot_files),
    void transport(1: map<string, string> col_ip),
    void start_sync_client(1: string url, 2: string path),
    void stop_sync_client(1: string url, 2: string path),
    void sync_del(1: set<Key> keys),
    string heartbeat(1: i32 beat),
    string status_cmd(1: string cmd, 2: list<string> values),
    string backup(1: string backup_type, 2: string subdir, 3: map<string, string> col_ip)
}
