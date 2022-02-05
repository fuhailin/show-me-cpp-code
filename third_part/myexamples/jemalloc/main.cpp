#include <jemalloc/jemalloc.h>
#include <unistd.h>

#include <ctime>
#include <iostream>
#include <string>
#include <vector>

class Widget {
 public:
  Widget() {}
  ~Widget() {}
  void hello() { std::cout << "hello, world" << std::endl; }

 private:
  std::string str_;
  char buf[1024];
  int i;
  int j;
  std::string str2_;
};

int main() {
  time_t t = time(NULL);
  for (int i = 0; i < 100000000; i++) {
    Widget* w = new Widget();
    delete w;
  }

  std::cout << "cost:" << time(NULL) - t << "s" << std::endl;
  return 0;
}
