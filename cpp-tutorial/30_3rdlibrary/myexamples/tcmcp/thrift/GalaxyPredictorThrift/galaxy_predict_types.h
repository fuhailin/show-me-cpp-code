/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef galaxy_predict_TYPES_H
#define galaxy_predict_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>




class ReqItem;

class Model;

class PredictReq;

class ResItem;

class PredictRes;

typedef struct _ReqItem__isset {
  _ReqItem__isset() : id(false), fids(false) {}
  bool id :1;
  bool fids :1;
} _ReqItem__isset;

class ReqItem : public virtual ::apache::thrift::TBase {
 public:

  ReqItem(const ReqItem&);
  ReqItem& operator=(const ReqItem&);
  ReqItem() : id() {
  }

  virtual ~ReqItem() throw();
  std::string id;
  std::vector<int64_t>  fids;

  _ReqItem__isset __isset;

  void __set_id(const std::string& val);

  void __set_fids(const std::vector<int64_t> & val);

  bool operator == (const ReqItem & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(fids == rhs.fids))
      return false;
    return true;
  }
  bool operator != (const ReqItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ReqItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ReqItem &a, ReqItem &b);

std::ostream& operator<<(std::ostream& out, const ReqItem& obj);

typedef struct _Model__isset {
  _Model__isset() : name(false), use_multi(false), tags(false) {}
  bool name :1;
  bool use_multi :1;
  bool tags :1;
} _Model__isset;

class Model : public virtual ::apache::thrift::TBase {
 public:

  Model(const Model&);
  Model& operator=(const Model&);
  Model() : name(), use_multi(0) {
  }

  virtual ~Model() throw();
  std::string name;
  bool use_multi;
  std::vector<std::string>  tags;

  _Model__isset __isset;

  void __set_name(const std::string& val);

  void __set_use_multi(const bool val);

  void __set_tags(const std::vector<std::string> & val);

  bool operator == (const Model & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (!(use_multi == rhs.use_multi))
      return false;
    if (!(tags == rhs.tags))
      return false;
    return true;
  }
  bool operator != (const Model &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Model & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Model &a, Model &b);

std::ostream& operator<<(std::ostream& out, const Model& obj);

typedef struct _PredictReq__isset {
  _PredictReq__isset() : req_items(false), models(false), handle_nums(false) {}
  bool req_items :1;
  bool models :1;
  bool handle_nums :1;
} _PredictReq__isset;

class PredictReq : public virtual ::apache::thrift::TBase {
 public:

  PredictReq(const PredictReq&);
  PredictReq& operator=(const PredictReq&);
  PredictReq() : handle_nums(0) {
  }

  virtual ~PredictReq() throw();
  std::vector<ReqItem>  req_items;
  std::vector<Model>  models;
  int16_t handle_nums;

  _PredictReq__isset __isset;

  void __set_req_items(const std::vector<ReqItem> & val);

  void __set_models(const std::vector<Model> & val);

  void __set_handle_nums(const int16_t val);

  bool operator == (const PredictReq & rhs) const
  {
    if (!(req_items == rhs.req_items))
      return false;
    if (!(models == rhs.models))
      return false;
    if (!(handle_nums == rhs.handle_nums))
      return false;
    return true;
  }
  bool operator != (const PredictReq &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PredictReq & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(PredictReq &a, PredictReq &b);

std::ostream& operator<<(std::ostream& out, const PredictReq& obj);

typedef struct _ResItem__isset {
  _ResItem__isset() : id(false), tag_scores(false) {}
  bool id :1;
  bool tag_scores :1;
} _ResItem__isset;

class ResItem : public virtual ::apache::thrift::TBase {
 public:

  ResItem(const ResItem&);
  ResItem& operator=(const ResItem&);
  ResItem() : id() {
  }

  virtual ~ResItem() throw();
  std::string id;
  std::map<std::string, std::vector<double> >  tag_scores;

  _ResItem__isset __isset;

  void __set_id(const std::string& val);

  void __set_tag_scores(const std::map<std::string, std::vector<double> > & val);

  bool operator == (const ResItem & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(tag_scores == rhs.tag_scores))
      return false;
    return true;
  }
  bool operator != (const ResItem &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ResItem & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ResItem &a, ResItem &b);

std::ostream& operator<<(std::ostream& out, const ResItem& obj);

typedef struct _PredictRes__isset {
  _PredictRes__isset() : res_items(false) {}
  bool res_items :1;
} _PredictRes__isset;

class PredictRes : public virtual ::apache::thrift::TBase {
 public:

  PredictRes(const PredictRes&);
  PredictRes& operator=(const PredictRes&);
  PredictRes() {
  }

  virtual ~PredictRes() throw();
  std::map<std::string, ResItem>  res_items;

  _PredictRes__isset __isset;

  void __set_res_items(const std::map<std::string, ResItem> & val);

  bool operator == (const PredictRes & rhs) const
  {
    if (!(res_items == rhs.res_items))
      return false;
    return true;
  }
  bool operator != (const PredictRes &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const PredictRes & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(PredictRes &a, PredictRes &b);

std::ostream& operator<<(std::ostream& out, const PredictRes& obj);



#endif
