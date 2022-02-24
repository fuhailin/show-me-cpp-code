#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        // return *max_element(dp.begin(), dp.end());
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {10, 9, 2, 5, 3, 7, 101, 18};
    int res = so.lengthOfLIS(test);
    cout << "res: " << res << endl;
    return 0;
}
