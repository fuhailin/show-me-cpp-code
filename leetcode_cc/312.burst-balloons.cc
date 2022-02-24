#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    vector<vector<int>> dp(nums.size() + 2, vector<int>(nums.size() + 2));
    vector<int> val(nums.size() + 2, 1);
    int res = INT_MIN;
    for (int i = 0; i < nums.size(); i++) {
      val[i + 1] = nums[i];
    }
    // 从下往上，所以要从短区间到长区间，i要倒序
    for (int i = nums.size() - 1; i >= 0; i--) {
      for (int j = i + 2; j < val.size(); j++) {
        for (int k = i + 1; k < j; k++) {
          dp[i][j] =
              max(dp[i][j], dp[i][k] + dp[k][j] + val[i] * val[k] * val[j]);
        }
      }
    }
    return dp[0][nums.size() + 1];
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {3, 1, 5, 8};
  int res = so.maxCoins(test);
  cout << res << endl;
  return 0;
}