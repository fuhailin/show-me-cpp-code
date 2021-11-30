#include "bits/stdc++.h"

class Solution {
    int binarySearchLower(vector<int>& nums, int target) {
        int left = -1, right = nums.size(), mid;
        while (left + 1 != right) {
            mid = left + ((right - left) >> 1);
            if (nums[mid] >= target) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return right;
    }

    int binarySearchUpper(vector<int>& nums, int target) {
        int left = -1, right = nums.size(), mid;
        while (left + 1 != right) {
            mid = left + ((right - left) >> 1);
            if (nums[mid] <= target) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return left;
    }

   public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = binarySearchLower(nums, target);
        int right = binarySearchUpper(nums, target);
        if (left <= right && right < nums.size() && nums[left] == target && nums[right] == target) {
            return {left, right};
        }
        return {-1, -1};
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {5, 7, 7, 8, 8, 10};
    vector<int> res = so.searchRange(test, 8);
    LOG(INFO) << "res: " << res;
    return 0;
}
