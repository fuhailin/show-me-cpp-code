#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

class Solution {
   public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 0);
        for (int i = 2; i < n; ++i) {
            if ((nums[i] - nums[i - 1]) == (nums[i - 1] - nums[i - 2])) {
                dp[i] = dp[i - 1] + 1;
            }
        }
        return accumulate(dp.begin(), dp.end(), 0);
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 2, 3, 4};
    int res = so.numberOfArithmeticSlices(test);
    cout << "res: " << res << endl;
    return 0;
}
