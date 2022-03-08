#include <iostream>
using namespace std;

// 正确，函数将永远不会返回。
[[noreturn]] void func1() { throw "error"; }

// 错误，如果用false进行调用，函数是会返回的，这时候会导致未定义行为。
[[noreturn]] void func2(bool b) {
  if (b) throw "error";
}

int main() {
  try {
    func1();
  } catch (char const* e) {
    std::cout << "Got something: " << e << "  \n";
  }

  // 此处编译会有警告信息。
  func2(false);
}