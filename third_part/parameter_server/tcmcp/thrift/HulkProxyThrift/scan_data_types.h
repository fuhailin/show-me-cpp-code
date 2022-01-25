/**
 * Autogenerated by Thrift Compiler (0.12.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef scan_data_TYPES_H
#define scan_data_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/stdcxx.h>


namespace hulk {

class ScanData;

typedef struct _ScanData__isset {
  _ScanData__isset() : RespData(false), IsEnd(false), cursor(false) {}
  bool RespData :1;
  bool IsEnd :1;
  bool cursor :1;
} _ScanData__isset;

class ScanData : public virtual ::apache::thrift::TBase {
 public:

  ScanData(const ScanData&);
  ScanData& operator=(const ScanData&);
  ScanData() : IsEnd(0), cursor() {
  }

  virtual ~ScanData() throw();
  std::map<std::string, std::string>  RespData;
  bool IsEnd;
  std::string cursor;

  _ScanData__isset __isset;

  void __set_RespData(const std::map<std::string, std::string> & val);

  void __set_IsEnd(const bool val);

  void __set_cursor(const std::string& val);

  bool operator == (const ScanData & rhs) const
  {
    if (!(RespData == rhs.RespData))
      return false;
    if (!(IsEnd == rhs.IsEnd))
      return false;
    if (!(cursor == rhs.cursor))
      return false;
    return true;
  }
  bool operator != (const ScanData &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ScanData & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ScanData &a, ScanData &b);

std::ostream& operator<<(std::ostream& out, const ScanData& obj);

} // namespace

#endif
