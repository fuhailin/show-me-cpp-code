#include <vector>
using namespace std;

class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        // dp[i]是以nums[i]结尾的最大自序和
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(nums[i] + dp[i - 1], nums[i]);
        }
        return dp[n - 1];
    }
};