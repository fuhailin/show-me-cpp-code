/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef GalaxyPredict_H
#define GalaxyPredict_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include "galaxy_predict_types.h"



#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class GalaxyPredictIf {
 public:
  virtual ~GalaxyPredictIf() {}
  virtual void predict(PredictRes& _return, const PredictReq& req) = 0;
};

class GalaxyPredictIfFactory {
 public:
  typedef GalaxyPredictIf Handler;

  virtual ~GalaxyPredictIfFactory() {}

  virtual GalaxyPredictIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(GalaxyPredictIf* /* handler */) = 0;
};

class GalaxyPredictIfSingletonFactory : virtual public GalaxyPredictIfFactory {
 public:
  GalaxyPredictIfSingletonFactory(const ::apache::thrift::stdcxx::shared_ptr<GalaxyPredictIf>& iface) : iface_(iface) {}
  virtual ~GalaxyPredictIfSingletonFactory() {}

  virtual GalaxyPredictIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(GalaxyPredictIf* /* handler */) {}

 protected:
  ::apache::thrift::stdcxx::shared_ptr<GalaxyPredictIf> iface_;
};

class GalaxyPredictNull : virtual public GalaxyPredictIf {
 public:
  virtual ~GalaxyPredictNull() {}
  void predict(PredictRes& /* _return */, const PredictReq& /* req */) {
    return;
  }
};

typedef struct _GalaxyPredict_predict_args__isset {
  _GalaxyPredict_predict_args__isset() : req(false) {}
  bool req :1;
} _GalaxyPredict_predict_args__isset;

class GalaxyPredict_predict_args {
 public:

  GalaxyPredict_predict_args(const GalaxyPredict_predict_args&);
  GalaxyPredict_predict_args& operator=(const GalaxyPredict_predict_args&);
  GalaxyPredict_predict_args() {
  }

  virtual ~GalaxyPredict_predict_args() throw();
  PredictReq req;

  _GalaxyPredict_predict_args__isset __isset;

  void __set_req(const PredictReq& val);

  bool operator == (const GalaxyPredict_predict_args & rhs) const
  {
    if (!(req == rhs.req))
      return false;
    return true;
  }
  bool operator != (const GalaxyPredict_predict_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GalaxyPredict_predict_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class GalaxyPredict_predict_pargs {
 public:


  virtual ~GalaxyPredict_predict_pargs() throw();
  const PredictReq* req;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _GalaxyPredict_predict_result__isset {
  _GalaxyPredict_predict_result__isset() : success(false) {}
  bool success :1;
} _GalaxyPredict_predict_result__isset;

class GalaxyPredict_predict_result {
 public:

  GalaxyPredict_predict_result(const GalaxyPredict_predict_result&);
  GalaxyPredict_predict_result& operator=(const GalaxyPredict_predict_result&);
  GalaxyPredict_predict_result() {
  }

  virtual ~GalaxyPredict_predict_result() throw();
  PredictRes success;

  _GalaxyPredict_predict_result__isset __isset;

  void __set_success(const PredictRes& val);

  bool operator == (const GalaxyPredict_predict_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const GalaxyPredict_predict_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GalaxyPredict_predict_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _GalaxyPredict_predict_presult__isset {
  _GalaxyPredict_predict_presult__isset() : success(false) {}
  bool success :1;
} _GalaxyPredict_predict_presult__isset;

class GalaxyPredict_predict_presult {
 public:


  virtual ~GalaxyPredict_predict_presult() throw();
  PredictRes* success;

  _GalaxyPredict_predict_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class GalaxyPredictClient : virtual public GalaxyPredictIf {
 public:
  GalaxyPredictClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  GalaxyPredictClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void predict(PredictRes& _return, const PredictReq& req);
  void send_predict(const PredictReq& req);
  void recv_predict(PredictRes& _return);
 protected:
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class GalaxyPredictProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::apache::thrift::stdcxx::shared_ptr<GalaxyPredictIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (GalaxyPredictProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_predict(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  GalaxyPredictProcessor(::apache::thrift::stdcxx::shared_ptr<GalaxyPredictIf> iface) :
    iface_(iface) {
    processMap_["predict"] = &GalaxyPredictProcessor::process_predict;
  }

  virtual ~GalaxyPredictProcessor() {}
};

class GalaxyPredictProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  GalaxyPredictProcessorFactory(const ::apache::thrift::stdcxx::shared_ptr< GalaxyPredictIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::apache::thrift::stdcxx::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::apache::thrift::stdcxx::shared_ptr< GalaxyPredictIfFactory > handlerFactory_;
};

class GalaxyPredictMultiface : virtual public GalaxyPredictIf {
 public:
  GalaxyPredictMultiface(std::vector<apache::thrift::stdcxx::shared_ptr<GalaxyPredictIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~GalaxyPredictMultiface() {}
 protected:
  std::vector<apache::thrift::stdcxx::shared_ptr<GalaxyPredictIf> > ifaces_;
  GalaxyPredictMultiface() {}
  void add(::apache::thrift::stdcxx::shared_ptr<GalaxyPredictIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void predict(PredictRes& _return, const PredictReq& req) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->predict(_return, req);
    }
    ifaces_[i]->predict(_return, req);
    return;
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class GalaxyPredictConcurrentClient : virtual public GalaxyPredictIf {
 public:
  GalaxyPredictConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  GalaxyPredictConcurrentClient(apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, apache::thrift::stdcxx::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
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
  void predict(PredictRes& _return, const PredictReq& req);
  int32_t send_predict(const PredictReq& req);
  void recv_predict(PredictRes& _return, const int32_t seqid);
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
