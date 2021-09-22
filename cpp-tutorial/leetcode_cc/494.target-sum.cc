#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;

    void backtracking(vector<int>& nums, int target, int sum, int idx) {
        if (sum == target) {
            res.emplace_back(path);
        }
        // 如果 sum + candidates[i] > target 就终止遍历
        for (int i = idx; i < nums.size() && sum + nums[i] <= target; i++) {
            path.push_back(nums[i]);
            backtracking(nums, target, sum + nums[i], i + 1);
            path.pop_back();
        }
    }

   public:
    /* backtracking
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (target > sum) return 0;        // 此时没有方案
        if ((target + sum) % 2) return 0;  // 此时没有方案，两个int相加的时候要各位小心数值溢出的问题
        int bagSize = (sum + target) / 2;
        sort(nums.begin(), nums.end());  // 需要排序
        backtracking(nums, bagSize, 0, 0);
        return res.size();
    }
    */
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        int diff = sum - target;
        if (diff < 0 || diff % 2 != 0) {
            return 0;
        }
        int n = nums.size(), neg = diff / 2;
        vector<int> dp(neg + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = neg; j >= nums[i - 1]; j--) {
                dp[j] = dp[j - nums[i - 1]] + dp[j];
            }
        }
        return dp[neg];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 1, 1, 1, 1};
    int res = so.findTargetSumWays(test, 3);
    cout << "res: " << res << endl;
    return 0;
}
