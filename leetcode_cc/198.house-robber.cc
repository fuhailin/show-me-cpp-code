#include <vector>
#include <iostream>

using namespace std;

class Solution {
   public:
    int rob(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums[0];
        }
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++) {
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return dp[nums.size() - 1];
    }
};

int main(int argc, char const *argv[])
{
    vector<int> test{1, 2, 3, 1};
    int res = Solution().rob(test);
    cout << boolalpha << res << endl;
    return 0;
}