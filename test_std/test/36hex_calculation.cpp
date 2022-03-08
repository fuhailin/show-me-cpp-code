/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      三十六进制加法
=============================================================================*/

#include <iostream>
#include <string>
using namespace std;

string add(const int& m, string a, string b) {
  int len1 = a.length(), len2 = b.length(), len = 0;
  if (len1 > len2) {
    len = len1;
    int temp = len1 - len2;
    b.insert(0, temp, '0');
  } else if (len2 > len1) {
    len = len2;
    int temp = len2 - len1;
    a.insert(0, temp, '0');
  } else {
    len = len1;
  }
  string sum;
  int remainder = 0, carry = 0;
  for (int i = len - 1; i >= 0; i--) {
    int one1 = a[i];
    int two1 = b[i];
    if (a[i] > '9') {
      one1 = a[i] - 'a' + 10;
    } else {
      one1 = a[i] - '0';
    }
    if (b[i] > '9') {
      two1 = b[i] - 'a' + 10;
    } else {
      two1 = b[i] - '0';
    }
    int temp = one1 + two1 + carry;
    remainder = temp % m;
    carry = temp / m;
    if (remainder > 9) {
      char ctemp = remainder + 'a' - 10;
      sum = sum + ctemp;
    } else {
      char ctemp = remainder + '0';
      sum = sum + ctemp;
    }
  }
  if (carry) {
    char ctemp = '0' + carry;
    sum = ctemp + sum;
  }
  return sum;
}

int main() {
  int hex;
  string a, b;
  cin >> hex >> a >> b;
  string res = add(hex, a, b);
  cout << a << " + " << b << " = " << res;
  return 0;
}
