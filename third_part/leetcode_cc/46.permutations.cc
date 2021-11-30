#include <gtest/gtest.h>

#include <vector>
using namespace std;

class Solution {
   private:
    vector<vector<int>> result;
    vector<int> path;
    void backtrack(vector<int>& nums, vector<bool>& used) {
        // 触发结束条件
        if (path.size() == nums.size()) {
            result.emplace_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == true) {
                continue;  // path里已经收录的元素，直接跳过
            }
            used[i] = true;
            path.emplace_back(nums[i]);  //# 做选择
            backtrack(nums, used);
            path.pop_back();  //# 撤销选择
            used[i] = false;  //将该选择再加入选择列表
        }
    }

   public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtrack(nums, used);
        return result;
    }
};

TEST(LeetCode, 全排列) {
    Solution s;
    {
        std::vector<std::vector<int>> inputs = {
            {1, 2, 3},
            {0, 1},
            {1}};

        vector<vector<vector<int>>> outputs = {
            {{{1, 2, 3}, {1, 3, 2}, {2, 1, 3}, {2, 3, 1}, {3, 1, 2}, {3, 2, 1}},
             {{0, 1}, {1, 0}},
             {{1}}};

        for (int i = 0; i < inputs.size(); ++i) {
            vector<vector<int>> ret = s.permute(inputs[i]);
            EXPECT_EQ(ret, outputs[i]);
        }
    }
}