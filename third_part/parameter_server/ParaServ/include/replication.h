
#ifndef LISTDB_REPLICATION_MASTER_H
#define LISTDB_REPLICATION_MASTER_H
#include <arpa/inet.h>  // inet_ntoa
#include <errno.h>
#include <fcntl.h>  // open
#include <inttypes.h>
#include <netdb.h>  // gethostbyname
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <rocksdb/status.h>
#include <signal.h>
#include <string.h>  // strerror
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>  // close

#include <condition_variable>
#include <iostream>
#include <map>
#include <mutex>
#include <set>
#include <thread>

#include "config.h"
#include "logger.h"
#include "logger.hpp"
#include "rocksdb/db.h"
#include "rocksdb/utilities/checkpoint.h"
#include "rocksdb/utilities/db_ttl.h"

#ifndef gettid
#define gettid() syscall(__NR_gettid)
#endif

#define DB_MAGIC 20180304
#define DB_VERSION_1 1
#define DB_BUFF_SIZE (1024 * 1024 * 2)
#define FILE_PERM (S_IRUSR | S_IWUSR | S_IWUSR | S_IRUSR)

int64_t read_64(const char *b);
int read_32(const char *b);
void write_32(int n, char *b);
void write_64(int64_t n, char *b);
ssize_t writen(int fd, const char *usrbuf, size_t n);
ssize_t readn(int fd, char *buf, ssize_t max_n, ssize_t n);

class BufferedWriter {
 private:
  int fd;
  size_t cap;
  size_t off;
  char *buf;

  int ensure_space(size_t n) {
    if (cap - off < n) {
      if (this->Flush() < 0) return -1;
    }
    return 0;
  }

 public:
  BufferedWriter(int fd, size_t cap)
      : fd(fd), cap(cap), off(0), buf((char *)malloc(cap)) {}

  ~BufferedWriter() { delete (buf); }

  int WriteByte(char c) {
    if (ensure_space(1) < 0) return -1;
    buf[off++] = c;
    return 0;
  }

  int Write32(int v) {
    if (ensure_space(4) < 0) return -1;
    write_32(v, buf + off);
    off += 4;
    return 0;
  }

  int Write64(int64_t v) {
    if (ensure_space(8) < 0) return -1;
    write_64(v, buf + off);
    off += 8;
    return 0;
  }

  int Write(const std::string &v) {
    // std::cout<<"======================"<<std::endl<<"write"<<std::endl<<"======================"<<std::endl;

    if (v.length() > cap) {  // value size较大，直接写，不buffer
      if (this->Flush() < 0) return -1;
      if (writen(fd, v.data(), v.length()) <= 0) return -1;
      return 0;
    }

    if (ensure_space(v.length()) < 0) return -1;
    memcpy(buf + off, v.data(), v.length());
    off += v.length();
    return 0;
  }

  int Flush() {
    if (off > 0) {
      if (writen(fd, buf, off) <= 0) return -1;
      off = 0;
    }
    return 0;
  }
};

class BufferedReader {
 private:
  int fd;
  size_t cap;
  char *buf;
  size_t read;   // 第一个可读的
  size_t limit;  // 最后一个可读取

  int read_more(size_t least) {
    if (limit - read < least) {
      if (least > cap) {  // 大空间
        this->cap = least + 512;
        char *tmp = (char *)malloc(this->cap);
        memcpy(tmp, buf + read, limit - read);
        free(this->buf);

        this->buf = tmp;
        this->limit = limit - read;
        this->read = 0;
      } else if (cap - limit < least) {  // 剩下的空间不够
        memmove(buf, buf + read, limit - read);
        this->limit = limit - read;
        this->read = 0;
      }

      ssize_t n = readn(fd, buf + limit, cap - limit, least - (limit - read));
      if (n <= 0) {
        return -1;
      }
      this->limit += n;
    }

    return 0;
  }

 public:
  BufferedReader(int fd, size_t cap)
      : fd(fd), cap(cap), buf((char *)malloc(cap)), read(0), limit(0) {}

  int Remain() { return limit - read; }

  void Reset(int fd) {
    this->fd = fd;
    this->read = 0;
    this->limit = 0;
  }

  int ReadByte(int *v) {
    if (read_more(1) < 0) return -1;
    *v = *(buf + read);
    this->read += 1;
    return 0;
  }

  // Error when return < 0
  int Read32(int *v) {
    if (read_more(4) < 0) return -1;
    *v = read_32(buf + read);
    this->read += 4;
    return 0;
  }

  int Read64(int64_t *v) {
    if (read_more(8) < 0) return -1;
    *v = read_64(buf + read);
    this->read += 8;
    return 0;
  }

  int Read(char **p, size_t size) {
    if (read_more(size) < 0) return -1;
    *p = buf + read;
    this->read += size;
    return 0;
  }

  ~BufferedReader() { delete (buf); }
};

struct SlaveInfo {
  const std::string host;
  const int port;
  const int fd;
  std::atomic<int64_t> seq;

  SlaveInfo(std::string &host, int port, int fd)
      : host(host), port(port), fd(fd), seq(0) {}
};

struct MasterOptions {
  rocksdb::DB *db;
  // check point dir. use db's dir for faster hard link

  BaseConfig *conf;
  std::mutex &mtx;  // write thread -> sync thread
  std::condition_variable &cv;

  // stats
  std::mutex l_mtx;  // protect local
  std::vector<SlaveInfo *> slaves;

  MasterOptions(rocksdb::DB *db, std::mutex &mtx, std::condition_variable &cv,
                BaseConfig *conf)
      : db(db), conf(conf), mtx(mtx), cv(cv) {}
};

class SequenceManager {
 private:
  std::atomic<int64_t> seq;
  int fd;

 public:
  SequenceManager() : seq(0), fd(-1) {}

  int Open(const std::string &dir, const std::string &host, const int port) {
    rocksdb::Env *env = rocksdb::Env::Default();
    const std::string fname =
        dir + "/" + host + "-" + std::to_string(port) + ".seq";
    uint64_t size = 0;
    env->GetFileSize(fname, &size);
    fd = open(fname.data(), O_RDWR | O_CREAT, FILE_PERM);
    if (fd < 0) {
      logger->error("[slave] open seq file {}, {}", fname.data(),
                    strerror(errno));
      return -1;
    }
    if (size == 8) {
      char buffer[8];
      if (readn(fd, buffer, 8, 8) < 8) {
        logger->error("[slave] seq file {}, {}", fname.data(), strerror(errno));
        return -1;
      }
      int64_t buf_tmp;
      memcpy(&buf_tmp, buffer, 8);
      // seq.store(*((int64_t *)buffer), std::memory_order_release);
      seq.store(buf_tmp, std::memory_order_release);
    }
    logger->info("[slave] read seq {} from {}", Get(), fname.data());
    return 0;
  }

  void Open(int64_t sequence) { seq = sequence; }

  int64_t Get() { return this->seq.load(std::memory_order_acquire); }

  int write(rocksdb::SequenceNumber n) {
    if (pwrite(fd, (char *)(&n), 8, 0) != 8) {
      logger->error("[slave] write seq {} fail, {}", n, strerror(errno));
      return -1;
    }
    this->seq.store(n, std::memory_order_release);
    return 0;
  }
};

int open_client(const std::string &server, int port, int64_t done_seq);
int open_listenfd(int port);
int write_live_files_to_slave_V2(MasterOptions *r_opt, SlaveInfo *si);
int handle_slave0(MasterOptions *r_opt, SlaveInfo &si);
void handle_slave(MasterOptions *r_opt, struct sockaddr_in c_addr, int fd);
int listen_and_serv(MasterOptions *r_opt, int listen_fd);
int start_master(MasterOptions *r_opt);

inline bool ends_with(std::string const &value, std::string const &ending) {
  if (ending.size() > value.size()) return false;
  return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

struct SlaveManager {
  BaseConfig *conf;

  int fd;
  BufferedReader *br;
  SequenceManager sm;

  // 主动同步用的
  std::mutex &mtx;
  std::condition_variable &cv;

  std::atomic<int64_t> master_seq;  // master's last seq
  int64_t slave_seq;

  void sync(rocksdb::DB *db) {  // 增量更新
    pid_t curTid = gettid();
    logger->info("SlaveManager::sync curTid: {}", curTid);

    while (1) {  // never exits
      const rocksdb::WriteOptions w_opt;
      int flags = 0, length;
      int64_t seq, latest_seq;
      char *content;

      while (1) {
        if (br->ReadByte(&flags) < 0 || br->Read64(&seq) < 0 ||
            br->Read64(&latest_seq) || br->Read32(&length) < 0 ||
            br->Read(&content, length) < 0) {
          // log_error("[slave] read change, seq %ld, %s", seq,
          // strerror(errno));
          logger->error("[slave] read change, seq  {}", strerror(errno));
          break;
        }

        if (flags != 0) return;
        if (length == 0) return;
        logger->info("seq: {} latest_seq {}", seq, latest_seq);
        logger->info("content len: {}", length);

        const std::string rep(content, length);
        rocksdb::WriteBatch wb(rep);
        const rocksdb::Status status = db->Write(w_opt, &wb);
        (void)status;

        master_seq.store(latest_seq, std::memory_order_release);
        if (conf->master_port > 0) {  // 通知连上这个slave的其他slave，有更新了
          cv.notify_all();
        }
      }

      close(fd);
      int seconds = conf->slave_retry_seconds;
      while (1) {
        logger->error("[slave] connection from %s:{} broken, seq {}, sleep {}",
                      conf->master.ip.data(), conf->master.port, sm.Get(),
                      seconds);
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        int t = open_client(conf->master.ip, conf->master.port, sm.Get());
        if (t > 0) {
          logger->error("[slave] connection to {}:{} ok, sync from seq {}",
                        conf->master.ip.data(), conf->master.port, sm.Get());
          this->fd = t;
          this->br->Reset(this->fd);
          break;
        }
        seconds += 1;
        if (seconds >= 3) {
          break;
        }
      }

      if (seconds >= 3) {
        break;
      }
    }
  }

 public:
  ~SlaveManager() {
    if (br != nullptr) delete (br);
  }

  SlaveManager(BaseConfig *conf, std::mutex &mtx, std::condition_variable &cv)
      : conf(conf), mtx(mtx), cv(cv) {
    master_seq = 0;
    br = nullptr;
  }

  SlaveManager(BaseConfig *conf, std::mutex &mtx, std::condition_variable &cv,
               int64_t slave_sequence)
      : conf(conf), mtx(mtx), cv(cv) {
    master_seq = 0;
    slave_seq = slave_sequence;
    br = nullptr;
  }

  int64_t GetSeq() { return sm.Get(); }

  int64_t MasterSeq() { return master_seq.load(std::memory_order_acquire); }

  int Open() {
    // if (sm.Open(conf->wal_dir.empty() ? conf->data_dir : conf->wal_dir,
    // conf->master.ip, conf->master.port) < 0)
    //     return -1;
    sm.Open(slave_seq);
    this->fd = open_client(conf->master.ip, conf->master.port, sm.Get());
    if (this->fd > 0) {
      br = new BufferedReader(this->fd, DB_BUFF_SIZE);
    }
    return this->fd;
  }

  // 从master，把dump的数据文件存在本地. 记录下来seq number
  int64_t InitDump() {
    int file_count, name_size;
    int64_t content_length, seq;
    char *fnp;

    if (br->Read32(&file_count) < 0) {
      logger->error("[slave] read file count, {}", strerror(errno));
      return -1;
    }

    logger->info("[slave] begin load {} live files from master", file_count);
    for (int i = 0; i < file_count; i++) {
      // read file_name, content_length
      if (br->Read32(&name_size) < 0 || br->Read(&fnp, name_size) < 0 ||
          br->Read64(&content_length)) {
        logger->error("[slave] read {}th file name, {}", i + 1,
                      strerror(errno));
        return -1;
      }

      std::string fname(fnp, name_size);
      if (!conf->wal_dir.empty() && ends_with(fname, ".log")) {
        // 配置了wal的路径后，.log文件需要copy到这个目录下
        fname = conf->wal_dir + "/" + fname;
      } else {
        fname = conf->data_dir + "/" + fname;
      }
      int ffd = open(fname.data(), O_WRONLY | O_CREAT, FILE_PERM);
      if (ffd < 0) {
        logger->error("[slave] create {}th file {}, {}", i + 1, fname.data(),
                      strerror(errno));
        return -1;
      }

      // 4) read content and write it to file
      while (content_length > 0) {
        int n = std::min<int>(content_length, br->Remain());
        if (n == 0) n = std::min<int>(content_length, 1024 * 1024);
        char *p;
        if (br->Read(&p, n) < 0) {
          logger->error("[slave] read {}th content, {}", i + 1,
                        strerror(errno));
          return -1;
        }
        size_t nleft = n;
        while (nleft > 0) {
          ssize_t nwritten;
          if ((nwritten = write(ffd, p, nleft)) <= 0) {
            if (errno == EINTR)
              n = 0;
            else {
              logger->error("[slave] write {}th content, {}", i + 1,
                            strerror(errno));
              return -1;
            };
          }
          nleft -= nwritten;
          p += nwritten;
        }

        content_length -= n;
      }
    }

    if (br->Read64(&seq) < 0) {
      logger->error("[slave] read seq, {}", strerror(errno));
      return -1;
    }

    if (sm.write(seq) >= 0) {
      logger->info(
          "[slave] done load {} live files from master, sync from seq {}",
          file_count, seq);
      return seq;
    } else {
      logger->error("[slave] write seq failed {}, {}", seq, strerror(errno));
      return -1;
    }
  }

  // 从master，把dump的数据文件存在本地. 记录下来seq number
  int64_t InitDump(rocksdb::DB *db,
                   std::vector<rocksdb::ColumnFamilyHandle *> &cfHandles);

  void StartSync(rocksdb::DB *db) {
    std::thread sync(&SlaveManager::sync, this, db);
    sync.detach();
  }
};

class RockServerBase {
 protected:
  BaseConfig *conf;

  // master slave replication
  std::mutex msMutex_;
  std::condition_variable msCondVar_;

  std::map<std::string, size_t> cfIndex;

  SlaveManager *sm;
  MasterOptions *m_opt;

  int64_t up_time;

  rocksdb::ColumnFamilyHandle *getCFHandle(const std::string &cf) {
    size_t index = 0;
    if (!cf.empty()) {
      auto it = cfIndex.find(cf);
      if (it != cfIndex.end()) {
        index = it->second;
      }
    }
    return cfHandles[index];
  }

 public:
  std::vector<rocksdb::ColumnFamilyHandle *> cfHandles;
  rocksdb::DB *db;
  inline void notify_replication() {
    if (conf->master_port > 0) {
      msCondVar_.notify_all();
    }
  }

  RockServerBase(BaseConfig *conf) : conf(conf) {
    sm = nullptr;
    m_opt = nullptr;
  }

  int Open0() {
    rocksdb::Options options;
    conf->setDBOptions(options);
    conf->printDBOptions(options);

    rocksdb::Status status;
    const std::string &db_dir = conf->data_dir;

    if (conf->mode == kModeMaster) {
      status = rocksdb::DB::ListColumnFamilies(options, db_dir,
                                               &(conf->columnFamilies));
      const std::vector<std::string> &cfNames = conf->columnFamilies;
      // for (const auto& cfName : cfNames) {
      // std::cout << "cfName: " << cfName << std::endl;
      // }

      std::vector<rocksdb::ColumnFamilyDescriptor> column_families;
      column_families.emplace_back(rocksdb::kDefaultColumnFamilyName,
                                   rocksdb::ColumnFamilyOptions(options));
      for (size_t i = 0; i != cfNames.size(); i++) {
        column_families.emplace_back(cfNames[i],
                                     rocksdb::ColumnFamilyOptions(options));
        cfIndex[cfNames[i]] = i + 1;
      }
      status =
          rocksdb::DB::Open(options, db_dir, column_families, &cfHandles, &db);

      if (!status.ok()) {
        logger->error("open db {}, {}", db_dir.data(),
                      status.ToString().data());
        return -1;
      }
    } else {
      std::vector<std::string> column_family_names;
      status = rocksdb::DB::ListColumnFamilies(options, db_dir,
                                               &column_family_names);
      std::vector<rocksdb::ColumnFamilyDescriptor> column_families;

      for (size_t i = 0; i != column_family_names.size(); i++) {
        column_families.emplace_back(column_family_names[i],
                                     rocksdb::ColumnFamilyOptions(options));
        cfIndex[column_family_names[i]] = i + 1;
      }
      if (column_families.size() == 0) {
        column_families.emplace_back(rocksdb::kDefaultColumnFamilyName,
                                     rocksdb::ColumnFamilyOptions(options));
      }

      status =
          rocksdb::DB::Open(options, db_dir, column_families, &cfHandles, &db);
      if (!status.ok()) {
        logger->error("open db {}, {}", db_dir.data(),
                      status.ToString().data());
        return -1;
      }
      int64_t seq = db->GetLatestSequenceNumber();
      sm = new SlaveManager(conf, msMutex_, msCondVar_, seq);
      if (sm->Open() < 0) return -1;
      if (column_families.size() == 1) {
        //这种情况说明slave的db文件夹中没有数据
        // std::cout << "Open0 11" << std::endl;
        sm->InitDump(db, cfHandles);
      }
      sm->StartSync(db);
    }
    db->GetEnv()->GetCurrentTime(&up_time);
    m_opt = new MasterOptions(db, msMutex_, msCondVar_, conf);
    if (conf->master_port > 0) {
      if (start_master(m_opt) < 0) return -1;
    }
    return 0;
  }
};

#endif  // LISTDB_REPLICATION_MASTER_H
