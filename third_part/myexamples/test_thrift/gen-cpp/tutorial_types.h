/**
 * Autogenerated by Thrift Compiler (0.15.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef tutorial_TYPES_H
#define tutorial_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>
#include "shared_types.h"


namespace tutorial {

/**
 * You can define enums, which are just 32 bit integers. Values are optional
 * and start at 1 if not supplied, C style again.
 */
struct Operation {
  enum type {
    ADD = 1,
    SUBTRACT = 2,
    MULTIPLY = 3,
    DIVIDE = 4
  };
};

extern const std::map<int, const char*> _Operation_VALUES_TO_NAMES;

std::ostream& operator<<(std::ostream& out, const Operation::type& val);

std::string to_string(const Operation::type& val);

/**
 * Thrift lets you do typedefs to get pretty names for your types. Standard
 * C style here.
 */
typedef int32_t MyInteger;

class Work;

class InvalidOperation;

typedef struct _Work__isset {
  _Work__isset() : num1(true), num2(false), op(false), comment(false) {}
  bool num1 :1;
  bool num2 :1;
  bool op :1;
  bool comment :1;
} _Work__isset;

/**
 * Structs are the basic complex data structures. They are comprised of fields
 * which each have an integer identifier, a type, a symbolic name, and an
 * optional default value.
 * 
 * Fields can be declared "optional", which ensures they will not be included
 * in the serialized output if they aren't set.  Note that this requires some
 * manual management in some languages.
 */
class Work : public virtual ::apache::thrift::TBase {
 public:

  Work(const Work&);
  Work& operator=(const Work&);
  Work() noexcept
       : num1(0),
         num2(0),
         op(static_cast<Operation::type>(0)),
         comment() {
  }

  virtual ~Work() noexcept;
  int32_t num1;
  int32_t num2;
  /**
   * 
   * @see Operation
   */
  Operation::type op;
  std::string comment;

  _Work__isset __isset;

  void __set_num1(const int32_t val);

  void __set_num2(const int32_t val);

  void __set_op(const Operation::type val);

  void __set_comment(const std::string& val);

  bool operator == (const Work & rhs) const
  {
    if (!(num1 == rhs.num1))
      return false;
    if (!(num2 == rhs.num2))
      return false;
    if (!(op == rhs.op))
      return false;
    if (__isset.comment != rhs.__isset.comment)
      return false;
    else if (__isset.comment && !(comment == rhs.comment))
      return false;
    return true;
  }
  bool operator != (const Work &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Work & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot) override;
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const override;

  virtual void printTo(std::ostream& out) const;
};

void swap(Work &a, Work &b);

std::ostream& operator<<(std::ostream& out, const Work& obj);

typedef struct _InvalidOperation__isset {
  _InvalidOperation__isset() : whatOp(false), why(false) {}
  bool whatOp :1;
  bool why :1;
} _InvalidOperation__isset;

/**
 * Structs can also be exceptions, if they are nasty.
 */
class InvalidOperation : public ::apache::thrift::TException {
 public:

  InvalidOperation(const InvalidOperation&);
  InvalidOperation& operator=(const InvalidOperation&);
  InvalidOperation() noexcept
                   : whatOp(0),
                     why() {
  }

  virtual ~InvalidOperation() noexcept;
  int32_t whatOp;
  std::string why;

  _InvalidOperation__isset __isset;

  void __set_whatOp(const int32_t val);

  void __set_why(const std::string& val);

  bool operator == (const InvalidOperation & rhs) const
  {
    if (!(whatOp == rhs.whatOp))
      return false;
    if (!(why == rhs.why))
      return false;
    return true;
  }
  bool operator != (const InvalidOperation &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const InvalidOperation & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept override;
};

void swap(InvalidOperation &a, InvalidOperation &b);

std::ostream& operator<<(std::ostream& out, const InvalidOperation& obj);

} // namespace

#endif
