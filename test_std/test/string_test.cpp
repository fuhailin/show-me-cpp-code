#include <iostream>
using namespace std;

#define N 100
int main() {
  char X[N];
  cin.getline(X, N);  //以cin.getline形式输入
  int a = 0, b = 0;
  for (int i = 0; i < N; i++) {
    if (X[i] == '#')  //为#为结束标志
      break;
    if (X[i] >= '0' && X[i] <= '9') a++;  //统计数字个数
    if ((X[i] >= 'a' && X[i] <= 'z') || (X[i] >= 'A' && X[i] <= 'Z'))
      b++;  //统计英文字母个数
  }
  cout << a << endl << b << endl;
  cout << X << endl;
  // strlen(X)<<
  // X.length()<<
  cout << X.size() << sizeof(X) << endl;
  return 0;
}