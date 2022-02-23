#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

void func(int a) {
  int i = 10;
  while (i--) {
    cout << "Hello World" << endl;
    std::this_thread::sleep_for(std::chrono::microseconds(50));
  }
}

int main(int argc, const char** argv) {
  std::thread thread1(func, 0);
  thread1.join();
  int j = 10;
  while (j--) {
    cout << "Hello Test" << endl;
    std::this_thread::sleep_for(std::chrono::microseconds(50));
  }
  return 0;
}