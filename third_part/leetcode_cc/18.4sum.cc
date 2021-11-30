#include "bits/stdc++.h"

class Solution {
    vector<vector<int>> twoSumTarget(vector<int>& nums, int start, int target) {
        // 左指针改为从 start 开始，其他不变
        int lo = start, hi = nums.size() - 1;
        vector<vector<int>> res;
        while (lo < hi) {
            int sum = nums[lo] + nums[hi];
            int left = nums[lo], right = nums[hi];
            if (sum < target) {
                while (lo < hi && nums[lo] == left) {
                    lo++;
                }
            } else if (sum > target) {
                while (lo < hi && nums[hi] == right) {
                    hi--;
                }
            } else {
                res.push_back({left, right});
                while (lo < hi && nums[lo] == left) {
                    lo++;
                };
                while (lo < hi && nums[hi] == right) {
                    hi--;
                };
            }
        }
        return res;
    }

    vector<vector<int>> threeSum(vector<int>& nums, int start, int target) {
        vector<vector<int>> res;
        // 穷举 threeSum 的第一个数
        for (int i = start; i < nums.size() - 2; i++) {
            // 对 target - nums[i] 计算 twoSum
            vector<vector<int>> tuples = twoSumTarget(nums, i + 1, target - nums[i]);
            // 如果存在满足条件的二元组，再加上 nums[i] 就是结果三元组
            for (vector<int>& tuple : tuples) {
                tuple.push_back(nums[i]);
                res.emplace_back(tuple);
            }
            // 跳过第一个数字重复的情况，否则会出现重复结果
            while (i < nums.size() - 1 && nums[i] == nums[i + 1]) i++;
        }
        return res;
    }

   public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        // 数组得排个序
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (int i = 0; i < n - 3; i++) {
            // 对 target - nums[i] 计算 twoSum
            vector<vector<int>> tuples = threeSum(nums, i + 1, target - nums[i]);
            // 如果存在满足条件的二元组，再加上 nums[i] 就是结果三元组
            for (vector<int>& tuple : tuples) {
                tuple.push_back(nums[i]);
                res.emplace_back(tuple);
            }
            // 跳过第一个数字重复的情况，否则会出现重复结果
            while (i < n - 2 && nums[i] == nums[i + 1]) i++;
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 0, -1, 0, -2, 2};
    auto res = so.fourSum(test, 0);
    LOG(INFO) << res;
    return 0;
}
