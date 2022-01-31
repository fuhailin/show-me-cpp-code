
#include <thrift/TToString.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TNonblockingServerSocket.h>
#include <thrift/transport/TServerSocket.h>

#include <memory>

#include "ParaServ.h"
#include "para_serv_op.h"
#include "parameter_server/common/logger.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

namespace ps {

class ParaServHandler : virtual public ps::ParaServIf {
 public:
  std::shared_ptr<ps::ParaServOP> ps_op_;
  ParaServHandler() : ps_op_(new ps::ParaServOP()) {}

  ParaServHandler(ps::Configure* conf_) : ps_op_(new ps::ParaServOP()) {
    ps_op_->conf = conf_;
    ps_op_->init();
  }

  void push(const std::map<ps::Key, std::string>& key_vals) {
    ps_op_->push(key_vals, false);
  }

  void sync_push(const std::map<ps::Key, std::string>& key_vals) {
    ps_op_->push(key_vals, true);
  }

  void pushemb(const std::map<ps::Key, std::string>& key_vals) {
    ps_op_->pushemb(key_vals);
  }

  void pushada(const std::map<ps::Key, std::string>& key_vals) {
    ps_op_->pushada(key_vals);
  }

  void pull(std::map<ps::Key, std::string>& _return,
            const std::set<ps::Key>& keys) {
    ps_op_->multi_pull(_return, keys);
  }

  void pull_online(std::map<ps::Key, std::string>& _return,
                   const std::set<ps::Key>& keys) {
    ps_op_->pull_online(_return, keys);
  }

  void status_cmd(std::string& _return, const std::string& cmd,
                  const std::vector<std::string>& values) {
    ps_op_->status_cmd(_return, cmd, values);
  }

  void start(const std::vector<int32_t>& cfList, const int32_t tot_files) {
    ps_op_->start(cfList, tot_files);
  }

  void copy_start(const std::vector<int32_t>& col_num,
                  const int32_t tot_files) {
    ps_op_->copy_start(col_num, tot_files);
  }

  void transport(const std::map<std::string, std::string>& col_ip) {
    ps_op_->transport(col_ip);
  }

  void start_sync_client(const std::string& url, const std::string& path) {
    ps_op_->start_sync_client(url, path);
  }

  void stop_sync_client(const std::string& url, const std::string& path) {
    ps_op_->stop_sync_client(url, path);
  }

  void sync_del(const std::set<Key>& keys) { ps_op_->del(keys); }

  void heartbeat(std::string& _return, const int32_t beat) {
    ps_op_->hearbeat(_return, beat);
  }

  void backup(std::string& _return, const std::string& backup_type,
              const std::string& subdir,
              const std::map<std::string, std::string>& col_ip) {
    ps_op_->backup(_return, backup_type, subdir, col_ip);
  }

  static std::shared_ptr<ParaServHandler> handler;
  static std::shared_ptr<ParaServHandler> getInstance() { return handler; }
  static void setInstance(std::shared_ptr<ParaServHandler> pInstance) {
    handler = pInstance;
  }
};
}  // namespace ps
