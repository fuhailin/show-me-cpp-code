#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> countBits(int n) {
    vector<int> res(n + 1);
    for (int i = 1; i <= n; i++) {
      if (i % 2 == 1) {
        res[i] = res[i - 1] + 1;
      } else {
          // 动态规划, res_i中1的个数与 res_i / 2 中 1的个数相同，因为去掉了最后的0；
        res[i] = res[i >> 1];
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> res = so.countBits(5);
  return 0;
}