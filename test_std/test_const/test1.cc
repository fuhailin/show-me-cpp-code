#include <iostream>
using namespace std;

class A {
  int data;

 public:
  A(int da = 100) : data(da) {}

  void display1() { cout << data << endl; }
  void display2() const { cout << data << endl; }
  void display3() const {
    data += 100;
    cout << data << endl;
  }
};

int main() {
  A a1;
  const A a2;
  a1.display1();
  a1.display2();
  a1.display3();  // error   ,const声明的成员函数不能改变数据成员的值
  a2.display1();  // error   ,const对象不能调用非const函数
  a2.display2();  // right
  a2.display3();  // error   ,const对象不能调用非const函数,且不能改变数据成员值
  return 0;
}