/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef psProxyServ_H
#define psProxyServ_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "ps_proxy_thrift_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class psProxyServIf {
 public:
  virtual ~psProxyServIf() {}
  virtual void push(const std::map<Key, std::string> & key_vals) = 0;
  virtual void sync_push(const std::map<Key, std::string> & key_vals) = 0;
  virtual void pushemb(const std::map<Key, std::string> & key_vals) = 0;
  virtual void pushada(const std::map<Key, std::string> & key_vals) = 0;
  virtual void pull(std::map<Key, std::string> & _return, const std::set<Key> & keys) = 0;
  virtual void pull_online(std::map<Key, std::string> & _return, const std::set<Key> & keys) = 0;
  virtual void replication(const std::string& zkUrl, const std::string& zkPath) = 0;
  virtual void copy_data(const std::map<std::string, std::string> & fileNum_ip) = 0;
  virtual void heartbeat(std::string& _return, const int32_t input) = 0;
};

class psProxyServIfFactory {
 public:
  typedef psProxyServIf Handler;

  virtual ~psProxyServIfFactory() {}

  virtual psProxyServIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(psProxyServIf* /* handler */) = 0;
};

class psProxyServIfSingletonFactory : virtual public psProxyServIfFactory {
 public:
  psProxyServIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<psProxyServIf>& iface) : iface_(iface) {}
  virtual ~psProxyServIfSingletonFactory() {}

  virtual psProxyServIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(psProxyServIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<psProxyServIf> iface_;
};

class psProxyServNull : virtual public psProxyServIf {
 public:
  virtual ~psProxyServNull() {}
  void push(const std::map<Key, std::string> & /* key_vals */) {
    return;
  }
  void sync_push(const std::map<Key, std::string> & /* key_vals */) {
    return;
  }
  void pushemb(const std::map<Key, std::string> & /* key_vals */) {
    return;
  }
  void pushada(const std::map<Key, std::string> & /* key_vals */) {
    return;
  }
  void pull(std::map<Key, std::string> & /* _return */, const std::set<Key> & /* keys */) {
    return;
  }
  void pull_online(std::map<Key, std::string> & /* _return */, const std::set<Key> & /* keys */) {
    return;
  }
  void replication(const std::string& /* zkUrl */, const std::string& /* zkPath */) {
    return;
  }
  void copy_data(const std::map<std::string, std::string> & /* fileNum_ip */) {
    return;
  }
  void heartbeat(std::string& /* _return */, const int32_t /* input */) {
    return;
  }
};

typedef struct _psProxyServ_push_args__isset {
  _psProxyServ_push_args__isset() : key_vals(false) {}
  bool key_vals :1;
} _psProxyServ_push_args__isset;

class psProxyServ_push_args {
 public:

  psProxyServ_push_args(const psProxyServ_push_args&);
  psProxyServ_push_args& operator=(const psProxyServ_push_args&);
  psProxyServ_push_args() {
  }

  virtual ~psProxyServ_push_args() throw();
  std::map<Key, std::string>  key_vals;

  _psProxyServ_push_args__isset __isset;

  void __set_key_vals(const std::map<Key, std::string> & val);

  bool operator == (const psProxyServ_push_args & rhs) const
  {
    if (!(key_vals == rhs.key_vals))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_push_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_push_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_push_pargs {
 public:


  virtual ~psProxyServ_push_pargs() throw();
  const std::map<Key, std::string> * key_vals;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _psProxyServ_sync_push_args__isset {
  _psProxyServ_sync_push_args__isset() : key_vals(false) {}
  bool key_vals :1;
} _psProxyServ_sync_push_args__isset;

class psProxyServ_sync_push_args {
 public:

  psProxyServ_sync_push_args(const psProxyServ_sync_push_args&);
  psProxyServ_sync_push_args& operator=(const psProxyServ_sync_push_args&);
  psProxyServ_sync_push_args() {
  }

  virtual ~psProxyServ_sync_push_args() throw();
  std::map<Key, std::string>  key_vals;

  _psProxyServ_sync_push_args__isset __isset;

  void __set_key_vals(const std::map<Key, std::string> & val);

  bool operator == (const psProxyServ_sync_push_args & rhs) const
  {
    if (!(key_vals == rhs.key_vals))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_sync_push_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_sync_push_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_sync_push_pargs {
 public:


  virtual ~psProxyServ_sync_push_pargs() throw();
  const std::map<Key, std::string> * key_vals;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_sync_push_result {
 public:

  psProxyServ_sync_push_result(const psProxyServ_sync_push_result&);
  psProxyServ_sync_push_result& operator=(const psProxyServ_sync_push_result&);
  psProxyServ_sync_push_result() {
  }

  virtual ~psProxyServ_sync_push_result() throw();

  bool operator == (const psProxyServ_sync_push_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const psProxyServ_sync_push_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_sync_push_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_sync_push_presult {
 public:


  virtual ~psProxyServ_sync_push_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _psProxyServ_pushemb_args__isset {
  _psProxyServ_pushemb_args__isset() : key_vals(false) {}
  bool key_vals :1;
} _psProxyServ_pushemb_args__isset;

class psProxyServ_pushemb_args {
 public:

  psProxyServ_pushemb_args(const psProxyServ_pushemb_args&);
  psProxyServ_pushemb_args& operator=(const psProxyServ_pushemb_args&);
  psProxyServ_pushemb_args() {
  }

  virtual ~psProxyServ_pushemb_args() throw();
  std::map<Key, std::string>  key_vals;

  _psProxyServ_pushemb_args__isset __isset;

  void __set_key_vals(const std::map<Key, std::string> & val);

  bool operator == (const psProxyServ_pushemb_args & rhs) const
  {
    if (!(key_vals == rhs.key_vals))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_pushemb_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pushemb_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pushemb_pargs {
 public:


  virtual ~psProxyServ_pushemb_pargs() throw();
  const std::map<Key, std::string> * key_vals;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pushemb_result {
 public:

  psProxyServ_pushemb_result(const psProxyServ_pushemb_result&);
  psProxyServ_pushemb_result& operator=(const psProxyServ_pushemb_result&);
  psProxyServ_pushemb_result() {
  }

  virtual ~psProxyServ_pushemb_result() throw();

  bool operator == (const psProxyServ_pushemb_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const psProxyServ_pushemb_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pushemb_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pushemb_presult {
 public:


  virtual ~psProxyServ_pushemb_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _psProxyServ_pushada_args__isset {
  _psProxyServ_pushada_args__isset() : key_vals(false) {}
  bool key_vals :1;
} _psProxyServ_pushada_args__isset;

class psProxyServ_pushada_args {
 public:

  psProxyServ_pushada_args(const psProxyServ_pushada_args&);
  psProxyServ_pushada_args& operator=(const psProxyServ_pushada_args&);
  psProxyServ_pushada_args() {
  }

  virtual ~psProxyServ_pushada_args() throw();
  std::map<Key, std::string>  key_vals;

  _psProxyServ_pushada_args__isset __isset;

  void __set_key_vals(const std::map<Key, std::string> & val);

  bool operator == (const psProxyServ_pushada_args & rhs) const
  {
    if (!(key_vals == rhs.key_vals))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_pushada_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pushada_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pushada_pargs {
 public:


  virtual ~psProxyServ_pushada_pargs() throw();
  const std::map<Key, std::string> * key_vals;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pushada_result {
 public:

  psProxyServ_pushada_result(const psProxyServ_pushada_result&);
  psProxyServ_pushada_result& operator=(const psProxyServ_pushada_result&);
  psProxyServ_pushada_result() {
  }

  virtual ~psProxyServ_pushada_result() throw();

  bool operator == (const psProxyServ_pushada_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const psProxyServ_pushada_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pushada_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pushada_presult {
 public:


  virtual ~psProxyServ_pushada_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _psProxyServ_pull_args__isset {
  _psProxyServ_pull_args__isset() : keys(false) {}
  bool keys :1;
} _psProxyServ_pull_args__isset;

class psProxyServ_pull_args {
 public:

  psProxyServ_pull_args(const psProxyServ_pull_args&);
  psProxyServ_pull_args& operator=(const psProxyServ_pull_args&);
  psProxyServ_pull_args() {
  }

  virtual ~psProxyServ_pull_args() throw();
  std::set<Key>  keys;

  _psProxyServ_pull_args__isset __isset;

  void __set_keys(const std::set<Key> & val);

  bool operator == (const psProxyServ_pull_args & rhs) const
  {
    if (!(keys == rhs.keys))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_pull_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pull_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pull_pargs {
 public:


  virtual ~psProxyServ_pull_pargs() throw();
  const std::set<Key> * keys;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _psProxyServ_pull_result__isset {
  _psProxyServ_pull_result__isset() : success(false) {}
  bool success :1;
} _psProxyServ_pull_result__isset;

class psProxyServ_pull_result {
 public:

  psProxyServ_pull_result(const psProxyServ_pull_result&);
  psProxyServ_pull_result& operator=(const psProxyServ_pull_result&);
  psProxyServ_pull_result() {
  }

  virtual ~psProxyServ_pull_result() throw();
  std::map<Key, std::string>  success;

  _psProxyServ_pull_result__isset __isset;

  void __set_success(const std::map<Key, std::string> & val);

  bool operator == (const psProxyServ_pull_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_pull_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pull_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _psProxyServ_pull_presult__isset {
  _psProxyServ_pull_presult__isset() : success(false) {}
  bool success :1;
} _psProxyServ_pull_presult__isset;

class psProxyServ_pull_presult {
 public:


  virtual ~psProxyServ_pull_presult() throw();
  std::map<Key, std::string> * success;

  _psProxyServ_pull_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _psProxyServ_pull_online_args__isset {
  _psProxyServ_pull_online_args__isset() : keys(false) {}
  bool keys :1;
} _psProxyServ_pull_online_args__isset;

class psProxyServ_pull_online_args {
 public:

  psProxyServ_pull_online_args(const psProxyServ_pull_online_args&);
  psProxyServ_pull_online_args& operator=(const psProxyServ_pull_online_args&);
  psProxyServ_pull_online_args() {
  }

  virtual ~psProxyServ_pull_online_args() throw();
  std::set<Key>  keys;

  _psProxyServ_pull_online_args__isset __isset;

  void __set_keys(const std::set<Key> & val);

  bool operator == (const psProxyServ_pull_online_args & rhs) const
  {
    if (!(keys == rhs.keys))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_pull_online_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pull_online_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_pull_online_pargs {
 public:


  virtual ~psProxyServ_pull_online_pargs() throw();
  const std::set<Key> * keys;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _psProxyServ_pull_online_result__isset {
  _psProxyServ_pull_online_result__isset() : success(false) {}
  bool success :1;
} _psProxyServ_pull_online_result__isset;

class psProxyServ_pull_online_result {
 public:

  psProxyServ_pull_online_result(const psProxyServ_pull_online_result&);
  psProxyServ_pull_online_result& operator=(const psProxyServ_pull_online_result&);
  psProxyServ_pull_online_result() {
  }

  virtual ~psProxyServ_pull_online_result() throw();
  std::map<Key, std::string>  success;

  _psProxyServ_pull_online_result__isset __isset;

  void __set_success(const std::map<Key, std::string> & val);

  bool operator == (const psProxyServ_pull_online_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_pull_online_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_pull_online_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _psProxyServ_pull_online_presult__isset {
  _psProxyServ_pull_online_presult__isset() : success(false) {}
  bool success :1;
} _psProxyServ_pull_online_presult__isset;

class psProxyServ_pull_online_presult {
 public:


  virtual ~psProxyServ_pull_online_presult() throw();
  std::map<Key, std::string> * success;

  _psProxyServ_pull_online_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _psProxyServ_replication_args__isset {
  _psProxyServ_replication_args__isset() : zkUrl(false), zkPath(false) {}
  bool zkUrl :1;
  bool zkPath :1;
} _psProxyServ_replication_args__isset;

class psProxyServ_replication_args {
 public:

  psProxyServ_replication_args(const psProxyServ_replication_args&);
  psProxyServ_replication_args& operator=(const psProxyServ_replication_args&);
  psProxyServ_replication_args() : zkUrl(), zkPath() {
  }

  virtual ~psProxyServ_replication_args() throw();
  std::string zkUrl;
  std::string zkPath;

  _psProxyServ_replication_args__isset __isset;

  void __set_zkUrl(const std::string& val);

  void __set_zkPath(const std::string& val);

  bool operator == (const psProxyServ_replication_args & rhs) const
  {
    if (!(zkUrl == rhs.zkUrl))
      return false;
    if (!(zkPath == rhs.zkPath))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_replication_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_replication_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_replication_pargs {
 public:


  virtual ~psProxyServ_replication_pargs() throw();
  const std::string* zkUrl;
  const std::string* zkPath;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_replication_result {
 public:

  psProxyServ_replication_result(const psProxyServ_replication_result&);
  psProxyServ_replication_result& operator=(const psProxyServ_replication_result&);
  psProxyServ_replication_result() {
  }

  virtual ~psProxyServ_replication_result() throw();

  bool operator == (const psProxyServ_replication_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const psProxyServ_replication_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_replication_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_replication_presult {
 public:


  virtual ~psProxyServ_replication_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _psProxyServ_copy_data_args__isset {
  _psProxyServ_copy_data_args__isset() : fileNum_ip(false) {}
  bool fileNum_ip :1;
} _psProxyServ_copy_data_args__isset;

class psProxyServ_copy_data_args {
 public:

  psProxyServ_copy_data_args(const psProxyServ_copy_data_args&);
  psProxyServ_copy_data_args& operator=(const psProxyServ_copy_data_args&);
  psProxyServ_copy_data_args() {
  }

  virtual ~psProxyServ_copy_data_args() throw();
  std::map<std::string, std::string>  fileNum_ip;

  _psProxyServ_copy_data_args__isset __isset;

  void __set_fileNum_ip(const std::map<std::string, std::string> & val);

  bool operator == (const psProxyServ_copy_data_args & rhs) const
  {
    if (!(fileNum_ip == rhs.fileNum_ip))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_copy_data_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_copy_data_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_copy_data_pargs {
 public:


  virtual ~psProxyServ_copy_data_pargs() throw();
  const std::map<std::string, std::string> * fileNum_ip;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_copy_data_result {
 public:

  psProxyServ_copy_data_result(const psProxyServ_copy_data_result&);
  psProxyServ_copy_data_result& operator=(const psProxyServ_copy_data_result&);
  psProxyServ_copy_data_result() {
  }

  virtual ~psProxyServ_copy_data_result() throw();

  bool operator == (const psProxyServ_copy_data_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const psProxyServ_copy_data_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_copy_data_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_copy_data_presult {
 public:


  virtual ~psProxyServ_copy_data_presult() throw();

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _psProxyServ_heartbeat_args__isset {
  _psProxyServ_heartbeat_args__isset() : input(false) {}
  bool input :1;
} _psProxyServ_heartbeat_args__isset;

class psProxyServ_heartbeat_args {
 public:

  psProxyServ_heartbeat_args(const psProxyServ_heartbeat_args&);
  psProxyServ_heartbeat_args& operator=(const psProxyServ_heartbeat_args&);
  psProxyServ_heartbeat_args() : input(0) {
  }

  virtual ~psProxyServ_heartbeat_args() throw();
  int32_t input;

  _psProxyServ_heartbeat_args__isset __isset;

  void __set_input(const int32_t val);

  bool operator == (const psProxyServ_heartbeat_args & rhs) const
  {
    if (!(input == rhs.input))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_heartbeat_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_heartbeat_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class psProxyServ_heartbeat_pargs {
 public:


  virtual ~psProxyServ_heartbeat_pargs() throw();
  const int32_t* input;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _psProxyServ_heartbeat_result__isset {
  _psProxyServ_heartbeat_result__isset() : success(false) {}
  bool success :1;
} _psProxyServ_heartbeat_result__isset;

class psProxyServ_heartbeat_result {
 public:

  psProxyServ_heartbeat_result(const psProxyServ_heartbeat_result&);
  psProxyServ_heartbeat_result& operator=(const psProxyServ_heartbeat_result&);
  psProxyServ_heartbeat_result() : success() {
  }

  virtual ~psProxyServ_heartbeat_result() throw();
  std::string success;

  _psProxyServ_heartbeat_result__isset __isset;

  void __set_success(const std::string& val);

  bool operator == (const psProxyServ_heartbeat_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const psProxyServ_heartbeat_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const psProxyServ_heartbeat_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _psProxyServ_heartbeat_presult__isset {
  _psProxyServ_heartbeat_presult__isset() : success(false) {}
  bool success :1;
} _psProxyServ_heartbeat_presult__isset;

class psProxyServ_heartbeat_presult {
 public:


  virtual ~psProxyServ_heartbeat_presult() throw();
  std::string* success;

  _psProxyServ_heartbeat_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class psProxyServClient : virtual public psProxyServIf {
 public:
  psProxyServClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  psProxyServClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void push(const std::map<Key, std::string> & key_vals);
  void send_push(const std::map<Key, std::string> & key_vals);
  void sync_push(const std::map<Key, std::string> & key_vals);
  void send_sync_push(const std::map<Key, std::string> & key_vals);
  void recv_sync_push();
  void pushemb(const std::map<Key, std::string> & key_vals);
  void send_pushemb(const std::map<Key, std::string> & key_vals);
  void recv_pushemb();
  void pushada(const std::map<Key, std::string> & key_vals);
  void send_pushada(const std::map<Key, std::string> & key_vals);
  void recv_pushada();
  void pull(std::map<Key, std::string> & _return, const std::set<Key> & keys);
  void send_pull(const std::set<Key> & keys);
  void recv_pull(std::map<Key, std::string> & _return);
  void pull_online(std::map<Key, std::string> & _return, const std::set<Key> & keys);
  void send_pull_online(const std::set<Key> & keys);
  void recv_pull_online(std::map<Key, std::string> & _return);
  void replication(const std::string& zkUrl, const std::string& zkPath);
  void send_replication(const std::string& zkUrl, const std::string& zkPath);
  void recv_replication();
  void copy_data(const std::map<std::string, std::string> & fileNum_ip);
  void send_copy_data(const std::map<std::string, std::string> & fileNum_ip);
  void recv_copy_data();
  void heartbeat(std::string& _return, const int32_t input);
  void send_heartbeat(const int32_t input);
  void recv_heartbeat(std::string& _return);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class psProxyServProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<psProxyServIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (psProxyServProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_push(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_sync_push(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_pushemb(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_pushada(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_pull(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_pull_online(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_replication(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_copy_data(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_heartbeat(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  psProxyServProcessor(::apache::thrift::stdcxx::shared_ptr<psProxyServIf> iface) :
    iface_(iface) {
    processMap_["push"] = &psProxyServProcessor::process_push;
    processMap_["sync_push"] = &psProxyServProcessor::process_sync_push;
    processMap_["pushemb"] = &psProxyServProcessor::process_pushemb;
    processMap_["pushada"] = &psProxyServProcessor::process_pushada;
    processMap_["pull"] = &psProxyServProcessor::process_pull;
    processMap_["pull_online"] = &psProxyServProcessor::process_pull_online;
    processMap_["replication"] = &psProxyServProcessor::process_replication;
    processMap_["copy_data"] = &psProxyServProcessor::process_copy_data;
    processMap_["heartbeat"] = &psProxyServProcessor::process_heartbeat;
  }

  virtual ~psProxyServProcessor() {}
};

class psProxyServProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  psProxyServProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< psProxyServIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< psProxyServIfFactory > handlerFactory_;
};

class psProxyServMultiface : virtual public psProxyServIf {
 public:
  psProxyServMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<psProxyServIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~psProxyServMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<psProxyServIf> > ifaces_;
  psProxyServMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<psProxyServIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void push(const std::map<Key, std::string> & key_vals) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->push(key_vals);
    }
    ifaces_[i]->push(key_vals);
  }

  void sync_push(const std::map<Key, std::string> & key_vals) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->sync_push(key_vals);
    }
    ifaces_[i]->sync_push(key_vals);
  }

  void pushemb(const std::map<Key, std::string> & key_vals) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->pushemb(key_vals);
    }
    ifaces_[i]->pushemb(key_vals);
  }

  void pushada(const std::map<Key, std::string> & key_vals) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->pushada(key_vals);
    }
    ifaces_[i]->pushada(key_vals);
  }

  void pull(std::map<Key, std::string> & _return, const std::set<Key> & keys) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->pull(_return, keys);
    }
    ifaces_[i]->pull(_return, keys);
    return;
  }

  void pull_online(std::map<Key, std::string> & _return, const std::set<Key> & keys) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->pull_online(_return, keys);
    }
    ifaces_[i]->pull_online(_return, keys);
    return;
  }

  void replication(const std::string& zkUrl, const std::string& zkPath) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->replication(zkUrl, zkPath);
    }
    ifaces_[i]->replication(zkUrl, zkPath);
  }

  void copy_data(const std::map<std::string, std::string> & fileNum_ip) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->copy_data(fileNum_ip);
    }
    ifaces_[i]->copy_data(fileNum_ip);
  }

  void heartbeat(std::string& _return, const int32_t input) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->heartbeat(_return, input);
    }
    ifaces_[i]->heartbeat(_return, input);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class psProxyServConcurrentClient : virtual public psProxyServIf {
 public:
  psProxyServConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  psProxyServConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void push(const std::map<Key, std::string> & key_vals);
  void send_push(const std::map<Key, std::string> & key_vals);
  void sync_push(const std::map<Key, std::string> & key_vals);
  int32_t send_sync_push(const std::map<Key, std::string> & key_vals);
  void recv_sync_push(const int32_t seqid);
  void pushemb(const std::map<Key, std::string> & key_vals);
  int32_t send_pushemb(const std::map<Key, std::string> & key_vals);
  void recv_pushemb(const int32_t seqid);
  void pushada(const std::map<Key, std::string> & key_vals);
  int32_t send_pushada(const std::map<Key, std::string> & key_vals);
  void recv_pushada(const int32_t seqid);
  void pull(std::map<Key, std::string> & _return, const std::set<Key> & keys);
  int32_t send_pull(const std::set<Key> & keys);
  void recv_pull(std::map<Key, std::string> & _return, const int32_t seqid);
  void pull_online(std::map<Key, std::string> & _return, const std::set<Key> & keys);
  int32_t send_pull_online(const std::set<Key> & keys);
  void recv_pull_online(std::map<Key, std::string> & _return, const int32_t seqid);
  void replication(const std::string& zkUrl, const std::string& zkPath);
  int32_t send_replication(const std::string& zkUrl, const std::string& zkPath);
  void recv_replication(const int32_t seqid);
  void copy_data(const std::map<std::string, std::string> & fileNum_ip);
  int32_t send_copy_data(const std::map<std::string, std::string> & fileNum_ip);
  void recv_copy_data(const int32_t seqid);
  void heartbeat(std::string& _return, const int32_t input);
  int32_t send_heartbeat(const int32_t input);
  void recv_heartbeat(std::string& _return, const int32_t seqid);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  ::apache::thrift::async::TConcurrentClientSyncInfo sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif



#endif
