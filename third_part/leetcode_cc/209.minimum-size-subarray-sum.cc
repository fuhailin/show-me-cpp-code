#include "bits/stdc++.h"

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        if (n == 0) {
            return 0;
        }
        int ans = INT_MAX, start = 0, end = 0, sum = 0;
        while (end < n) {
            sum += nums[end];
            while (sum >= target) {
                ans = min(ans, end - start + 1);
                sum -= nums[start];
                start++;
            }
            end++;
        }
        return ans == INT_MAX ? 0 : ans;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {2, 3, 1, 2, 4, 3};
    int res = so.minSubArrayLen(7, test);
    cout << "res: " << res << endl;
    return 0;
}
