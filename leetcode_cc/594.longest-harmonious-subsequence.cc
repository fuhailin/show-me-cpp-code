#include "bits/stdc++.h"

class Solution {
   public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = INT_MIN;
        int left = 0;
        for (int right = 0; right < nums.size(); right++) {
            while ((nums[right] - nums[left]) > 1) {
                left++;
            }
            if ((nums[right] - nums[left]) == 1) {
                res = max(res, right - left + 1);
            }
        }
        return res == INT_MIN ? 0 : res;
    }
};