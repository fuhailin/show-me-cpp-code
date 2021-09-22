#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int findLengthOfLCIS(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return 1;
        int res = 0;
        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] < nums[i]) {
                dp[i] = dp[i - 1] + 1;
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test{1, 3, 5, 4, 7};
    int res = so.findLengthOfLCIS(test);
    cout << "res: " << res << endl;
    return 0;
}
