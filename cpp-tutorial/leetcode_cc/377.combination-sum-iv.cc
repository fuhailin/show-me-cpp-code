#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        //dp[i]表示容量为i的背包有几种组合方式
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for (int i = 1; i <= target; ++i) {
            for (int& num : nums) {
                if (num <= i && dp[i] + dp[i - num] < INT_MAX) {
                    dp[i] += dp[i - num];
                }
            }
        }
        return dp[target];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 2, 3};
    int res = so.combinationSum4(test, 4);
    cout << "result: " << res << endl;
    return 0;
}