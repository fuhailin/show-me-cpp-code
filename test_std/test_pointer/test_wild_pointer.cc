#include <iostream>
#include <string>
using namespace std;

int main() {
  //   string test = "fuhailin";
  //   string* p = &test;
  string* p = {"hello", "world"};
  cout << "*p:\t" << *p << endl;
  cout << "p:\t" << p << endl;
  cout << "&p:\t" << &p << endl;  // 0x7ff7bfefee98
  //   free(p);  // p 所指的内存被释放，但是p所指的地址仍然不变
  //   if (p != NULL)         // 没有起到防错作用
  //     strcpy(p, "world");  // 出错
  //   printf("% s \n", p);
}
