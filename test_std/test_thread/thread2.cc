#include <atomic>
#include <iostream>
#include <thread>
using namespace std;

// std::atomic<int> gloabalVariable = {0};
int gloabalVariable = 0;

void func(int a) {
  for (int i = 0; i < 100000000; i++) {
    gloabalVariable++;
    gloabalVariable--;
  }
}

int main(int argc, const char** argv) {
  std::thread thread1(func, 1000000);
  std::thread thread2(func, 1000000);

  thread1.join();
  // cout << "thread1 done." << endl;
  thread2.join();
  // cout << "thread2 done." << endl;
  cout << "current value is " << gloabalVariable << endl;

  return 0;
}