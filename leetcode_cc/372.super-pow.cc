#include <iostream>
#include <vector>

using namespace std;

class Solution {
  int MOD = 1337;
  long long quickMul(long long x, int N) {
    long long ans = 1;
    long long x_contribute = x;
    while (N > 0) {
      if (N % 2 == 1) {
        ans *= x_contribute % MOD;
      }
      x_contribute *= x_contribute % MOD;
      N >>= 1;
    }
    return ans;
  }

public:
  int superPow(int a, vector<int> &b) {
      if(b.empty()) {
          return 1;
      }
      int z = b.back();
      b.pop_back();
      return quickMul(a, z) % MOD * quickMul(superPow(a, b), 10) % MOD;
  }
};
