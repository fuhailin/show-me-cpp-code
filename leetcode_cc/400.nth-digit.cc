#include <math.h>

#include <iostream>

using namespace std;

class Solution {
 public:
  int findNthDigit(int n) {
    int d = 1, count = 9;
    while (n > (long)d * count) {
      n -= d * count;
      d++;
      count *= 10;
    }
    int index = n - 1;  // 从0 开始计数要减1
    int start = (int)pow(10, d - 1);
    int num = start + index / d;  // 那个数字
    int digitIndex = index % d;   // 那个数字的第几位
    string theNumber = to_string(num);
    char theChar = theNumber[digitIndex];
    int digit = theChar - '0';
    return digit;
  }
};

int main(int argc, char const *argv[]) {
  Solution so;
  int res = so.findNthDigit(11);
  cout << res << endl;
  return 0;
}
