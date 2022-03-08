#ifndef DESIGNPATTERN_SINGLETON_H
#define DESIGNPATTERN_SINGLETON_H
#include <mutex>
#include <string>
using namespace std;

/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */
class Singleton {
  /**
   * The Singleton's constructor/destructor should always be private to
   * prevent direct construction/desctruction calls with the `new`/`delete`
   * operator.
   */
 private:
  static Singleton* pinstance_;
  static std::mutex mutex_;

 protected:
  Singleton(const std::string value) : value_(value) {}
  ~Singleton() {}
  std::string value_;

 public:
  /**
   * Singletons should not be cloneable.
   */
  Singleton(Singleton& other) = delete;  //显示删除拷贝构造函数，禁止对象复制
  /**
   * Singletons should not be assignable.
    等号运算符重载
    注意，这个类似复制构造函数，将=右边的本类对象的值复制给等号左边的对象，它不属于构造函数，等号左右两边的对象必须已经被创建
    若没有显示的写=运算符重载，则系统也会创建一个默认的=运算符重载，只做一些基本的拷贝工作
   */
  void operator=(const Singleton&) = delete;

  /**
   * This is the static method that controls the access to the singleton
   * instance. On the first run, it creates a singleton object and places it
   * into the static field. On subsequent runs, it returns the client existing
   * object stored in the static field.
   static成员函数里面不能访问非静态成员变量，也不能调用非静态成员函数。
   静态成员函数不能为virtual修饰。
   */
  static Singleton* GetInstance(const std::string& value);
  /**
   * Finally, any singleton should define some business logic, which can be
   * executed on its instance.
   */
  void SomeBusinessLogic() {
    // ...
  }

  std::string value() const { return value_; }
};

#endif  // DESIGNPATTERN_SINGLETON_H
