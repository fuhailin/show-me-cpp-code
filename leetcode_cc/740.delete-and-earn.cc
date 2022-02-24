//
// Created by 趙大寳 on 2021/9/6.
//

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> note;
        sort(nums.begin(), nums.end());
        vector<int> new_nums = {0};
        for (int num : nums) {
            note[num]++;
            if (num != new_nums.back()) {
                new_nums.push_back(num);
            }
        }

        size_t n = new_nums.size();
        vector<int> dp(n, 0);
        dp[1] = new_nums[1] * note[new_nums[1]];
        for (int i = 2; i < n; ++i) {
            if ((new_nums[i] - new_nums[i - 1]) == 1) {
                dp[i] = max(dp[i - 1], dp[i - 2] + new_nums[i] * note[new_nums[i]]);
            } else {
                dp[i] = dp[i - 1] + new_nums[i] * note[new_nums[i]];
            }
        }
        return dp[n - 1];
    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    vector<int> test = {2, 2, 3, 3, 3, 4};
    int res = s.deleteAndEarn(test);
    cout << "res: " << res << endl;
    return 0;
}
