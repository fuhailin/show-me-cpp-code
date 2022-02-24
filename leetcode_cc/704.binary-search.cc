#include "bits/stdc++.h"

class Solution {
   public:
    int search(vector<int>& nums, int target) {
        int left = -1, right = nums.size(), mid;
        while (left + 1 != right) {
            mid = left + ((right - left) >> 1);
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return nums[right] == target ? right : -1;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {-1, 0};
    int res = so.search(test, 2);
    LOG(INFO) << "res: " << res;
    return 0;
}
