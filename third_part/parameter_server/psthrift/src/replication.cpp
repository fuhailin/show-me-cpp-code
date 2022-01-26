/*
 * @Company: TWL
 * @Author: xue jian
 * @Email: xuejian@kanzhun.com
 * @Date: 2019-08-22 20:55:19
 * @LastEditTime: 2019-08-23 11:56:03
 */
#include "config.h"
#include "replication.h"
#include <iostream>
using namespace std;


int parse_log_level(const std::string &level) {
    int l = util::Logger::kLevelInfo;
    if (level == "info") l = util::Logger::kLevelInfo;
    if (level == "trace") l = util::Logger::kLevelTrace;
    if (level == "debug") l = util::Logger::kLevelDebug;
    if (level == "warn") l = util::Logger::kLevelWarn;
    if (level == "error") l = util::Logger::kLevelError;
    return l;
}


int64_t read_64(const char *b) {
    auto *buf = (unsigned char *)b;
    return (int64_t)(buf[7]) | ((int64_t)(buf[6]) << 8) | ((int64_t)(buf[5]) << 16) | ((int64_t)(buf[4]) << 24) |
           ((int64_t)(buf[3]) << 32) | ((int64_t)(buf[2]) << 40) | ((int64_t)(buf[1]) << 48) |
           ((int64_t)(buf[0]) << 56);
}

int read_32(const char *b) {
    auto *buf = (unsigned char *)b;
    return ((int)(buf[3]) | ((int)(buf[2]) << 8) | ((int)(buf[1]) << 16) | ((int)(buf[0]) << 24));
}

void write_32(int n, char *b) {
    auto *buf = (unsigned char *)b;
    buf[3] = (unsigned char)(n & 0xff);
    buf[2] = (unsigned char)(n >> 8);
    buf[1] = (unsigned char)(n >> 16);
    buf[0] = (unsigned char)(n >> 24);
}

void write_64(int64_t n, char *b) {
    auto *buf = (unsigned char *)b;
    buf[7] = (unsigned char)(n);
    buf[6] = (unsigned char)(n >> 8);
    buf[5] = (unsigned char)(n >> 16);
    buf[4] = (unsigned char)(n >> 24);
    buf[3] = (unsigned char)(n >> 32);
    buf[2] = (unsigned char)(n >> 40);
    buf[1] = (unsigned char)(n >> 48);
    buf[0] = (unsigned char)(n >> 56);
}

ssize_t writen(int fd, const char *usrbuf, size_t n) {
    size_t nleft = n;
    ssize_t nwritten;
    const char *bufp = usrbuf;

    while (nleft > 0) {
        int flags = 0;
#ifdef MSG_NOSIGNAL
        flags = flags | MSG_NOSIGNAL;
#endif
        if ((nwritten = send(fd, bufp, nleft, flags)) <= 0) {
            if (errno == EINTR) /* interrupted by sig handler return */
                nwritten = 0;   /* and call write() again */
            else
                return -1; /* errorno set by write() */
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}

ssize_t readn(int fd, char *buf, ssize_t max_n, ssize_t n) {
    ssize_t cnt = 0;
    while (cnt < n) {
        ssize_t _n = read(fd, buf + cnt, max_n - cnt);
        if (_n < 0) {
            if (errno != EINTR) /* interrupted by sig handler return */
                return -1;
        }
        if (_n == 0) return 0;  // EOF
        cnt += _n;
    }
    return cnt;
}



int open_client(const std::string &server, int port, int64_t done_seq) {
    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    struct hostent *host = gethostbyname(server.data());
    if (host == nullptr) {
        close(fd);
        log_error("[slave] no such host: %s", server.data());
        return -1;
    }

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons((unsigned short)port);
    memcpy(&serveraddr.sin_addr, host->h_addr_list[0], host->h_length);

    if (connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        log_error("[slave] connect %s:%d %s", server.data(), port, strerror(errno));
        close(fd);
        return -1;
    }

    // write init sync packet
    BufferedWriter bw(fd, 32);
    if (bw.Write32(DB_MAGIC) < 0 || bw.Write32(DB_VERSION_1) < 0 || bw.Write64(done_seq + 1) < 0 || bw.Flush() < 0) {
        log_error("[slave] write sync seq %s:%d %s", server.data(), port, strerror(errno));
        close(fd);
        return -1;
    }

    int magic, version;
    BufferedReader br(fd, 8);
    if (br.Read32(&magic) < 0 || br.Read32(&version) < 0 || magic != DB_MAGIC || version != DB_VERSION_1) {
        log_error("[slave] read init packet %s:%d %s", server.data(), port, strerror(errno));
        close(fd);
        return -1;
    }
    return fd;
}

int open_listenfd(int port) {
    int listenfd, optval = 1;
    struct sockaddr_in serveraddr;

    /* Create a socket descriptor */
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

    // https://jvns.ca/blog/2015/11/21/why-you-should-understand-a-little-about-tcp/
    /* Eliminates "Address already in use" error from bind. */
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int)) < 0) return -1;

#ifdef TCP_CORK
    // 6 is TCP's protocol number
    // enable this, much faster : 4000 req/s -> 17000 req/s
    if (setsockopt(listenfd, 6, TCP_CORK, (const void *)&optval, sizeof(int)) < 0) return -1;
#endif

    /* Listenfd will be an endpoint for all requests to port
       on any IP address for this host */
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)port);

    if (bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) return -1;

    /* Make it a listening socket ready to accept connection requests */
    if (listen(listenfd, 1024) < 0) return -1;
    return listenfd;
}

void rm_rf_dir(rocksdb::Env *env, const std::string &tmp_dir, int fd) {
    if (fd > 0) close(fd);
    std::vector<std::string> files;
    env->GetChildren(tmp_dir, &files);
    for (auto &f : files) {
        if (f == "." || f == "..") continue;
        env->DeleteFile(tmp_dir + "/" + f);
    }
    env->DeleteDir(tmp_dir);
}

int write_live_files_to_slave(MasterOptions *r_opt, SlaveInfo *si, rocksdb::SequenceNumber *seq) {
    rocksdb::DB *db = r_opt->db;



    // slave第一次连上来，把所有的文件copy给slave
    std::string tmp_dir = r_opt->conf->data_dir + "/slave_" + si->host + "_" + std::to_string(si->port);
    rocksdb::Env *env = db->GetEnv();
    const rocksdb::Status &s0 = env->CreateDirIfMissing(tmp_dir);
    if (!s0.ok()) {
        log_error("[master] create dir %s, %s", tmp_dir.data(), s0.ToString().data());
        return -1;
    }

    // 1). create check point
    const rocksdb::DBOptions &opt = db->GetDBOptions();
    db->DisableFileDeletions();
    /*
    rocksdb::CheckpointImpl checkpoint(db);
    const rocksdb::Status &s_ = checkpoint.CreateCustomCheckpoint(
        opt,
        [&](const std::string &src_dir, const std::string &fname, rocksdb::FileType type) {
            // link_file_cb
            const rocksdb::Status &status = env->LinkFile(src_dir + fname, tmp_dir + fname);
            log_info("[master] link %s%s type %d, %s", src_dir.data(), fname.data(), type, status.ToString().data());
            return status;
        },
        [&](const std::string &src_dir, const std::string &fname, uint64_t size_limit_bytes,
            rocksdb::FileType type) {  // copy_file_cb
            const rocksdb::Status &status =
                CopyFile(env, src_dir + fname, tmp_dir + fname, size_limit_bytes, opt.use_fsync);
                //cout<<fname<<endl;
            log_info("[master] copy %s%s size %lu type %d, %s", src_dir.data(), fname.data(), size_limit_bytes, type,
                     status.ToString().data());
            return status;
        },
        [&](const std::string &fname, const std::string contents, rocksdb::FileType type) {
            // create_file_cb
            const rocksdb::Status &status = CreateFile(env, tmp_dir + fname, contents, opt.use_fsync);
            log_info("[master] create file %s, type %d, %s", fname.data(), type, status.ToString().data());
            return status;
        },
        seq, rocksdb::port::kMaxUint64);

    //const rocksdb::Status &s_ = checkpoint.CreateCheckpoint(tmp_dir, rocksdb::port::kMaxUint64);


    if (!s_.ok()) {
        log_error("[master] create checkpoint %s", s_.ToString().data());
        //exit(true);

        rm_rf_dir(env, tmp_dir, 0);
        return -1;
    }
    */
    db->EnableFileDeletions(false);

    log_info("[master] check point done for %s:%d, seq %lu", si->host.data(), si->port, *seq);

    // 2). write all files to client
    std::vector<std::string> files;
    env->GetChildren(tmp_dir, &files);
    int file_cnt = 0;
    for (auto &f : files) {
        if (f == "." || f == "..") continue;
        file_cnt += 1;
    }
    BufferedWriter bw(si->fd, 1024 * 32);
    bw.Write32(file_cnt);
    log_info("[master] begin send %d files to %s:%d", file_cnt, si->host.data(), si->port);

    for (auto &f : files) {
        if (f == "." || f == "..") continue;

        //cout<<f<<endl;

        uint64_t size;
        std::string fname = tmp_dir + "/" + f;
        env->GetFileSize(fname, &size);

        // file_name_length, file_name, file_length
        if (bw.Write32(f.length()) < 0 || bw.Write(f) < 0 || bw.Write64(size) < 0 || bw.Flush() < 0) {
            log_error("[master] write file name %s, %s", fname.data(), strerror(errno));
            rm_rf_dir(env, tmp_dir, 0);
            return -1;
        }

        int ffd = open(fname.data(), O_RDONLY);
        if (ffd < 0) {
            log_error("[master] open file %s, %s", fname.data(), strerror(errno));
            rm_rf_dir(env, tmp_dir, ffd);
            return -1;
        }

/*#ifdef OS_MACOSX
        off_t offset = 0, sent = size;
        while (offset < size) {
            // write file contents
            if (sendfile(ffd, si->fd, offset, &sent, nullptr, 0) < 0) {
                if (errno != EINTR) {
                    log_error("[master] send file %s, %s", fname.data(), strerror(errno));
                    rm_rf_dir(env, tmp_dir, ffd);
                    return -1;
                }
            }
            offset += sent;
            sent = size - offset;
        }
#elif defined OS_LINUX*/
        size_t sent = 0;
        while (sent < size) {
            ssize_t n = sendfile(si->fd, ffd, nullptr, size - sent);
            if (n < 0) {
                if (errno != EINTR) {
                    log_error("[master] send file %s, %s", fname.data(), strerror(errno));
                    rm_rf_dir(env, tmp_dir, ffd);
                    return -1;
                }
            }
            sent += n;
        }
//#endif
        close(ffd);
    }
    log_info("[master] send %d files to %s:%d done", file_cnt, si->host.data(), si->port);

    // 3). write seq number
    if (bw.Write64(*seq) < 0 || bw.Flush() < 0) {
        log_error("[master] write seq %lu, %s", *seq, strerror(errno));
        rm_rf_dir(env, tmp_dir, 0);
        return -1;
    }
    rm_rf_dir(env, tmp_dir, 0);
    return 0;
}

int handle_slave0(MasterOptions *r_opt, SlaveInfo &si) {
    /*
    protocol: numbers are big endian

    c: magic(4) + version(4) + sequence(8)
        if sequence <  0:  dump live files && write changes to c
        if sequence >= 0:  write changes to c

    dump live files:
        1. file_count(4): file_name_length(4) + file_name + file_length(8) + file_content
        2. sequence(8)
    write changes:
        flags byte + sequence(8) + master's latest seq(8) + change_length(4) + change_content
     */

    int magic, version;
    int64_t sequence;
    {
        BufferedReader br(si.fd, 16);
        if (br.Read32(&magic) < 0 || br.Read32(&version) < 0 || br.Read64(&sequence) < 0) {
            log_error("[master] read init packet %s:%d %s", si.host.data(), si.port, strerror(errno));
            return -1;
        }
        if (magic != DB_MAGIC || version != DB_VERSION_1) {
            log_error("[master] expect %s:%d with magic %d -> %d, version %d -> %d", si.host.data(), si.port, DB_MAGIC,
                      magic, DB_VERSION_1, version);
            return -1;
        }
        BufferedWriter bw(si.fd, 32);
        if (bw.Write32(DB_MAGIC) < 0 || bw.Write32(DB_VERSION_1) < 0 || bw.Flush() < 0) {
            log_error("[master] write init packet %s:%d %s", si.host.data(), si.port, strerror(errno));
            return -1;
        }
    }
    log_info("[master] slave connected, %s:%d, seq %ld", si.host.data(), si.port, sequence);

    rocksdb::DB *db = r_opt->db;
    rocksdb::SequenceNumber _seq = sequence;
    if (sequence < 0 && write_live_files_to_slave(r_opt, &si, &_seq)) {
        return -1;
    }
    si.seq.store(sequence, std::memory_order_release);

    // write changes
    log_info("[master] begin sync changes to %s:%d, from seq %lu", si.host.data(), si.port, _seq);
    std::unique_ptr<rocksdb::TransactionLogIterator> iter;
    assert(_seq >= 0);
    while (1) {
        auto status = db->GetUpdatesSince(_seq, &iter);

        if (status.IsNotFound()) {  // 等待更新
            {
                std::unique_lock<std::mutex> lck(r_opt->mtx);
                r_opt->cv.wait(lck);
            }
            continue;
        }
        if (!status.ok()) {
            log_error("[master] GetUpdatesSince seq %lu, %s", _seq, status.ToString().data());
            return -1;
        }
        break;
    }

    BufferedWriter bw(si.fd, DB_BUFF_SIZE);  // 2M buffer
    while (true) {
        for (; iter->Valid(); iter->Next()) {
            const rocksdb::BatchResult &b = iter->GetBatch();
            const std::string &change = b.writeBatchPtr->Data();
            _seq = b.sequence;
            si.seq.store(_seq, std::memory_order_release);
            if (bw.WriteByte(0) < 0 ||                            // flag 0
                bw.Write64(_seq) < 0 ||                           // seq number
                bw.Write64(db->GetLatestSequenceNumber()) < 0 ||  // seq number
                bw.Write32(change.length()) < 0 ||                // data length
                bw.Write(change) < 0) {                           // data
                goto error;
            }
        }

        if (bw.Flush() < 0) {
        error:
            log_error("[master] sync change with seq %lu to %s:%d, %s", _seq, si.host.data(), si.port, strerror(errno));
            return -1;
        }

        while (!iter->Valid()) {
        //std::cout<<"======================"<<std::endl<<"hehe"<<std::endl<<"======================"<<std::endl;
            {  // 等待更新
                std::unique_lock<std::mutex> lck(r_opt->mtx);
                r_opt->cv.wait(lck);
            }
        //std::cout<<"======================"<<std::endl<<"haha"<<std::endl<<"======================"<<std::endl;
            iter->Next();
            if (!iter->Valid()) {  // TODO 搞清楚这里为什么会这样，新日志文件?这是写入来，但是seq错了？然后就加一个seq？
                db->GetUpdatesSince(_seq + 1, &iter);
            }
        }
    }
}

void handle_slave(MasterOptions *r_opt, struct sockaddr_in c_addr, int fd) {
    char *c_host = inet_ntoa(c_addr.sin_addr);
    int c_port = ntohs(c_addr.sin_port);
    std::string host(c_host);

    SlaveInfo sl(host, c_port, fd);
    {
        std::lock_guard<std::mutex> _(r_opt->l_mtx);
        r_opt->slaves.push_back(&sl);
    }

    handle_slave0(r_opt, sl);
    close(fd);

    {
        std::lock_guard<std::mutex> _(r_opt->l_mtx);
        std::vector<SlaveInfo *> tmp(r_opt->slaves);
        r_opt->slaves.clear();
        for (auto it : tmp) {
            if (it != &sl) r_opt->slaves.push_back(it);
        }
    }
}



int listen_and_serv(MasterOptions *r_opt, int listen_fd) {
    while (1) {
        struct sockaddr_in clientaddr;
        socklen_t clientlen = sizeof clientaddr;
        int fd = accept(listen_fd, (struct sockaddr *)&clientaddr, &clientlen);
        if (fd < 0) {
            log_error("[master] accept, %s", strerror(errno));
            return fd;
        }

        std::thread slave(handle_slave, r_opt, clientaddr, fd);
        slave.detach();
    }
}

int start_master(MasterOptions *r_opt) {
    int listen_fd = open_listenfd(r_opt->conf->master_port);
    if (listen_fd < 0) {
        log_error("[master] on port %d, %s", r_opt->conf->master_port, strerror(errno));
        return -1;
    }
    log_info("[master] listens on port %d", r_opt->conf->master_port);
    std::thread master(listen_and_serv, r_opt, listen_fd);
    master.detach();
    return 0;
}