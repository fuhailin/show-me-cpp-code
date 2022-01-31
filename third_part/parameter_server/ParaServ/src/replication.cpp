#include "replication.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "assert_exit.h"
// #include "config.h"
#include "external_util.h"
#include "para_serv_handler.h"
using namespace std;

extern const int kFileNum;

int parse_log_level(const std::string& level) {
  int l = util::Logger::kLevelInfo;
  if (level == "info") l = util::Logger::kLevelInfo;
  if (level == "trace") l = util::Logger::kLevelTrace;
  if (level == "debug") l = util::Logger::kLevelDebug;
  if (level == "warn") l = util::Logger::kLevelWarn;
  if (level == "error") l = util::Logger::kLevelError;
  return l;
}

int64_t read_64(const char* b) {
  auto* buf = (unsigned char*)b;
  return (int64_t)(buf[7]) | ((int64_t)(buf[6]) << 8) |
         ((int64_t)(buf[5]) << 16) | ((int64_t)(buf[4]) << 24) |
         ((int64_t)(buf[3]) << 32) | ((int64_t)(buf[2]) << 40) |
         ((int64_t)(buf[1]) << 48) | ((int64_t)(buf[0]) << 56);
}

int read_32(const char* b) {
  auto* buf = (unsigned char*)b;
  return ((int)(buf[3]) | ((int)(buf[2]) << 8) | ((int)(buf[1]) << 16) |
          ((int)(buf[0]) << 24));
}

void write_32(int n, char* b) {
  auto* buf = (unsigned char*)b;
  buf[3] = (unsigned char)(n & 0xff);
  buf[2] = (unsigned char)(n >> 8);
  buf[1] = (unsigned char)(n >> 16);
  buf[0] = (unsigned char)(n >> 24);
}

void write_64(int64_t n, char* b) {
  auto* buf = (unsigned char*)b;
  buf[7] = (unsigned char)(n);
  buf[6] = (unsigned char)(n >> 8);
  buf[5] = (unsigned char)(n >> 16);
  buf[4] = (unsigned char)(n >> 24);
  buf[3] = (unsigned char)(n >> 32);
  buf[2] = (unsigned char)(n >> 40);
  buf[1] = (unsigned char)(n >> 48);
  buf[0] = (unsigned char)(n >> 56);
}

ssize_t writen(int fd, const char* usrbuf, size_t n) {
  size_t nleft = n;
  ssize_t nwritten;
  const char* bufp = usrbuf;

  while (nleft > 0) {
    int flags = 0;
#ifdef MSG_NOSIGNAL
    flags = flags | MSG_NOSIGNAL;
#endif
    if ((nwritten = send(fd, bufp, nleft, flags)) <= 0) {
      if (errno == EINTR) /* interrupted by sig handler return */
        nwritten = 0;     /* and call write() again */
      else
        return -1; /* errorno set by write() */
    }
    nleft -= nwritten;
    bufp += nwritten;
  }
  return n;
}

ssize_t readn(int fd, char* buf, ssize_t max_n, ssize_t n) {
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

int open_client(const std::string& server, int port, int64_t done_seq) {
  int fd;
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

  struct hostent* host = gethostbyname(server.data());
  if (host == nullptr) {
    close(fd);
    logger->error("[slave] no such host: {}", server.data());
    return -1;
  }

  struct sockaddr_in serveraddr;
  memset(&serveraddr, 0, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons((unsigned short)port);
  memcpy(&serveraddr.sin_addr, host->h_addr_list[0], host->h_length);

  if (connect(fd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
    logger->error("[slave] connect {}:{} {}", server.data(), port,
                  strerror(errno));
    close(fd);
    return -1;
  }

  // write init sync packet
  int magic, version;
  BufferedReader br(fd, 8);
  if (br.Read32(&magic) < 0 || br.Read32(&version) < 0 || magic != DB_MAGIC ||
      version != DB_VERSION_1) {
    logger->error("[slave] read init packet {}:{} {}", server.data(), port,
                  strerror(errno));
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
  if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval,
                 sizeof(int)) < 0)
    return -1;

#ifdef TCP_CORK
  // 6 is TCP's protocol number
  // enable this, much faster : 4000 req/s -> 17000 req/s
  if (setsockopt(listenfd, 6, TCP_CORK, (const void*)&optval, sizeof(int)) < 0)
    return -1;
#endif

  /* Listenfd will be an endpoint for all requests to port
     on any IP address for this host */
  memset(&serveraddr, 0, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)port);

  if (bind(listenfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    return -1;

  /* Make it a listening socket ready to accept connection requests */
  if (listen(listenfd, 1024) < 0) return -1;
  return listenfd;
}

void rm_rf_dir(rocksdb::Env* env, const std::string& tmp_dir, int fd) {
  if (fd > 0) close(fd);
  std::vector<std::string> files;
  env->GetChildren(tmp_dir, &files);
  for (auto& f : files) {
    if (f == "." || f == "..") continue;
    env->DeleteFile(tmp_dir + "/" + f);
  }
  env->DeleteDir(tmp_dir);
}

int write_live_files_to_slave(MasterOptions* r_opt, SlaveInfo* si,
                              rocksdb::SequenceNumber* seq) {
  auto handler = ps::ParaServHandler::getInstance();
  std::shared_ptr<ps::ParaServOP> psop = handler->ps_op_;
  std::string mn_id;
  auto conf = psop->conf;
  auto db = psop->db;

  conf->getmodelname(mn_id);

  {
    std::shared_ptr<storage_tool> t = storage_tool::Instance();
    std::string ip = t->user_password;
    std::string mkdir_command("sshpass -p ");
    mkdir_command += ip;
    mkdir_command += " ssh -o StrictHostKeyChecking=no root@";
    mkdir_command += si->host;
    mkdir_command += " \'mkdir -p /data/transport/";
    mkdir_command += mn_id;
    mkdir_command += ";\n exit\'";
    logger->info("mk remote dir command is: {}", mkdir_command);
    system(mkdir_command.data());
    logger->info("make dir in {} success!!", ip);
  }

  rocksdb::Checkpoint* checkpoint;
  rocksdb::Status status = rocksdb::Checkpoint::Create(db, &checkpoint);
  rocksdb::Env* env = db->GetEnv();
  std::string snap_dir = conf->data_dir + "/snap";
  system((std::string("rm -fr ") + snap_dir).c_str());
  status = env->CreateDir(snap_dir);
  logger->info("snap_dir = {}", snap_dir);
  if (!status.ok()) {
    logger->error("fail to create snap_dir");
    return -1;
  }

  return 0;
}

int handle_slave0(MasterOptions* r_opt, SlaveInfo& si) {
  /*
  protocol: numbers are big endian

  c: magic(4) + version(4) + sequence(8)
      if sequence <  0:  dump live files && write changes to c
      if sequence >= 0:  write changes to c

  dump live files:
      1. file_count(4): file_name_length(4) + file_name + file_length(8) +
  file_content
      2. sequence(8)
  write changes:
      flags byte + sequence(8) + master's latest seq(8) + change_length(4) +
  change_content
   */

  logger->info("[master] slave connected, {}:{}", si.host.data(), si.port);
  rocksdb::DB* db = r_opt->db;

  if (write_live_files_to_slave_V2(r_opt, &si)) {
    return -1;
  }

  //
  BufferedWriter bw_init(si.fd, 32);
  if (bw_init.Write32(DB_MAGIC) < 0 || bw_init.Write32(DB_VERSION_1) < 0 ||
      bw_init.Flush() < 0) {
    logger->error("[master] write init packet {}:{} {}", si.host.data(),
                  si.port, strerror(errno));
    return -1;
  }

  int magic, version;
  int64_t sequence;
  {
    BufferedReader br(si.fd, 16);
    if (br.Read32(&magic) < 0 || br.Read32(&version) < 0 ||
        br.Read64(&sequence) < 0) {
      logger->error("[master] read init packet {}:{} {}", si.host.data(),
                    si.port, strerror(errno));
      return -1;
    }
    if (magic != DB_MAGIC || version != DB_VERSION_1) {
      logger->error(
          "[master] expect {}:{} with magic {} -> {}, version {} -> {}",
          si.host.data(), si.port, DB_MAGIC, magic, DB_VERSION_1, version);
      return -1;
    }
  }
  rocksdb::SequenceNumber _seq = sequence;
  si.seq.store(sequence, std::memory_order_release);

  // write changes
  logger->info("[master] begin sync changes to {}:{}, from seq {}",
               si.host.data(), si.port, _seq);
  std::unique_ptr<rocksdb::TransactionLogIterator> iter;

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
      logger->error("[master] GetUpdatesSince seq {}, {}", _seq,
                    status.ToString().data());
      return -1;
    }
    logger->info("new key wrote");
    break;
  }

  BufferedWriter bw(si.fd, DB_BUFF_SIZE);  // 2M buffer
  while (true) {
    for (; iter->Valid(); iter->Next()) {
      logger->info("transmit new batch");
      const rocksdb::BatchResult& b = iter->GetBatch();
      const std::string& change = b.writeBatchPtr->Data();
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
      logger->error("[master] sync change with seq {} to {}:{}, {}", _seq,
                    si.host.data(), si.port, strerror(errno));
      return -1;
    }

    while (!iter->Valid()) {
      // std::cout<<"======================"<<std::endl<<"hehe"<<std::endl<<"======================"<<std::endl;
      {  // 等待更新
        std::unique_lock<std::mutex> lck(r_opt->mtx);
        r_opt->cv.wait(lck);
      }
      // std::cout<<"======================"<<std::endl<<"haha"<<std::endl<<"======================"<<std::endl;
      iter->Next();
      if (!iter->Valid()) {  // TODO
                             // 搞清楚这里为什么会这样，新日志文件?这是写入来，但是seq错了？然后就加一个seq？
        db->GetUpdatesSince(_seq + 1, &iter);
      }
    }
  }
}

void handle_slave(MasterOptions* r_opt, struct sockaddr_in c_addr, int fd) {
  pid_t curTid = gettid();
  logger->info("handle_slave curTid: {}", curTid);
  char* c_host = inet_ntoa(c_addr.sin_addr);
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
    std::vector<SlaveInfo*> tmp(r_opt->slaves);
    r_opt->slaves.clear();
    for (auto it : tmp) {
      if (it != &sl) r_opt->slaves.push_back(it);
    }
  }
}

int listen_and_serv(MasterOptions* r_opt, int listen_fd) {
  pid_t curTid = gettid();
  logger->info("listen_and_serv curTid: {}", curTid);
  while (1) {
    struct sockaddr_in clientaddr;
    socklen_t clientlen = sizeof clientaddr;
    int fd = accept(listen_fd, (struct sockaddr*)&clientaddr, &clientlen);
    if (fd < 0) {
      logger->error("[master] accept, {}", strerror(errno));
      return fd;
    }

    std::thread slave(handle_slave, r_opt, clientaddr, fd);
    slave.detach();
  }
}

int start_master(MasterOptions* r_opt) {
  int listen_fd = open_listenfd(r_opt->conf->master_port);
  if (listen_fd < 0) {
    logger->error("[master] on port {}, {}", r_opt->conf->master_port,
                  strerror(errno));
    return -1;
  }
  logger->info("[master] listens on port {}", r_opt->conf->master_port);
  std::thread master(listen_and_serv, r_opt, listen_fd);
  master.detach();
  return 0;
}

int write_live_files_to_slave_V2(MasterOptions* r_opt, SlaveInfo* si) {
  // std::cout << "-----1----" << std::endl;
  auto storage_tool = storage_tool::Instance();
  auto handler = ps::ParaServHandler::getInstance();
  std::shared_ptr<ps::ParaServOP> psop = handler->ps_op_;
  std::string mn_id;
  auto conf = psop->conf;
  auto db = psop->db;
  conf->getmodelname(mn_id);

  // std::string sshpass_command = std::string("sshpass -p ") +
  // storage_tool->user_password;
  std::string sshpass_command;

  {
    std::string ip = si->host;
    std::string mkdir_command =
        sshpass_command + " ssh -o StrictHostKeyChecking=no ";
    mkdir_command += ip;
    mkdir_command += " \'mkdir -p /data/transport/";
    mkdir_command += mn_id;
    mkdir_command += ";\n exit\'";
    logger->info("whole command is: {}", mkdir_command);
    system(mkdir_command.data());
    logger->info("make dir in {} success!!", ip);
  }

  rocksdb::Checkpoint* checkpoint;
  rocksdb::Status status = rocksdb::Checkpoint::Create(db, &checkpoint);
  rocksdb::Env* env = db->GetEnv();
  std::string snap_dir = conf->data_dir + "/snap";
  system((std::string("rm -fr ") + snap_dir).c_str());
  status = env->CreateDir(snap_dir);
  std::string rm_command("rm -rf ");
  rm_command += snap_dir;

  logger->info("snap_dir = {}", snap_dir);
  if (!status.ok()) {
    logger->error("fail to create snap_dir");
    system(rm_command.data());
    return -1;
  }

  for (auto& tmp_handle : psop->cfHandles) {
    rocksdb::ExportImportFilesMetaData* metadata = nullptr;
    std::string col_dir = snap_dir + "/" + tmp_handle.first;
    status =
        checkpoint->ExportColumnFamily(tmp_handle.second, col_dir, &metadata);
    if (!status.ok()) {
      logger->error("export cf failed, col_dir={}", col_dir);
      break;
    }

    auto j_meta = get_json_from_sstmeta(*metadata);
    std::string file_name = col_dir + "/" + "metafile";
    std::ofstream metafile(file_name);
    metafile << j_meta;
    metafile.close();

    std::string scp_command =
        sshpass_command + " scp -o StrictHostKeyChecking=no -r ";
    scp_command =
        scp_command + col_dir + " " + si->host + ":/data/transport/" + mn_id;
    logger->info("begin transport {}: {}", col_dir, log_Time());
    system(scp_command.data());
    logger->info("{}", scp_command.data());
    logger->info("end transport {}: {}", col_dir, log_Time());
  }
  system(rm_command.data());

  return 0;
}

int64_t SlaveManager::InitDump(
    rocksdb::DB* db, std::vector<rocksdb::ColumnFamilyHandle*>& cfHandles) {
  logger->info("initdump begin");
  auto cf = ps::Configure::Instance();
  std::string mn_id;
  cf->getmodelname(mn_id);
  std::string dest_dir = "/data/transport/" + mn_id + "/";

  logger->info("col_num = {}; dest_dir = {}", kFileNum, dest_dir);

  for (int col = 0; col < kFileNum; col++) {
    rocksdb::ColumnFamilyHandle* cf_handle_to_create = nullptr;
    logger->info("col_name = {}", col);
    std::string col_name = std::to_string(col);
    std::string col_dir = dest_dir + col_name;
    std::string metafile_name(col_dir + "/metafile");

    std::ifstream metafile(metafile_name);
    logger->info("metafile_name = {}", metafile_name);
    if (!metafile.is_open()) {
      continue;
    }
    logger->info("after_get metafile = {}", metafile_name);
    json j_meta;
    metafile >> j_meta;
    metafile.close();
    logger->info("after_get jmeta = {}", metafile_name);
    if (j_meta.empty()) {
      logger->error("can't get the meta message!");
      assert(0);
    }
    if (j_meta["files"].size() == 0) {
      rocksdb::Status status = db->CreateColumnFamily(
          rocksdb::ColumnFamilyOptions(), col_name, &cf_handle_to_create);
      if (status.ok()) {
        cfHandles.push_back(cf_handle_to_create);
      } else {
        logger->error("create cf failed: cf {}", col);
        assert(status.ok());
      }
      continue;
    }
    for (auto& file : j_meta["files"]) {
      file["db_path"] = col_dir;
      file["column_family_name"] = col_name;
    }

    rocksdb::ExportImportFilesMetaData metadata(get_sstmeta_from_json(j_meta));
    rocksdb::ImportColumnFamilyOptions i_options;
    rocksdb::Status status;
    rocksdb::ColumnFamilyOptions cf_option;

    try {
      status = db->CreateColumnFamilyWithImport(cf_option, col_name, i_options,
                                                metadata, &cf_handle_to_create);
    } catch (std::exception& e) {
      logger->error("exception caught: {}", e.what());
      logger->error("create column family failed.");
      assert_exit(0);
    }

    logger->info("after create = {}", metafile_name);
    if (status.ok()) {
      logger->info("success create the {} column!!", col_name);
    } else {
      logger->error("can't create the {} column!!", col_name);
      assert(0);
    }
    cfHandles.push_back(cf_handle_to_create);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  std::string rm_command("rm -rf ");
  rm_command += dest_dir;

  logger->info("rm_command = {}", rm_command.data());

  int64_t seq = db->GetLatestSequenceNumber();

  logger->info("db latest sequence is {}", seq);
  BufferedWriter bw(fd, 32);
  if (bw.Write32(DB_MAGIC) < 0 || bw.Write32(DB_VERSION_1) < 0 ||
      bw.Write64(seq + 1) < 0 || bw.Flush() < 0) {
    logger->error("[slave] write sync error: {}", strerror(errno));
    close(fd);
    return -1;
  }

  logger->info("initdump ok");
  return 0;
}
