#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
   public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int maxNum = *max_element(nums.begin(), nums.end());
        if (sum & 1) return false;
        int target = sum / 2;
        if (maxNum > target) return false;
        int n = nums.size();
        // dp[i][j] 前i个数字是否和为j
        vector<bool> dp(target + 1, false);
        dp[0] = false;
        dp[nums[0]] = true;
        // 遍历物品
        for (int i = 1; i < n; ++i) {
            // 遍历容量
            for (int j = target; j >= nums[i]; j--) {
                if (dp[target]) {
                    return true;
                }
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 5, 11, 5};
    bool res = so.canPartition(test);
    cout << "res: " << res << endl;
    return 0;
}
