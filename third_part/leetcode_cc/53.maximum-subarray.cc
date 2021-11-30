#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        // dp[i]表示以
        vector<int> dp(n);
        dp[0] = nums[0];
        int res = dp[0];
        for (int i = 1; i < n; i++) {
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
            res = max(res, dp[i]);
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res = so.maxSubArray(test);
    cout << "res: " << res << endl;
    return 0;
}
