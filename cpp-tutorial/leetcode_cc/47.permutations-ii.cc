#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> result;
    vector<int> path;
    void backtrack(vector<int>& nums, vector<bool>& visited) {
        // 触发结束条件
        if (path.size() == nums.size()) {
            result.emplace_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (visited[i] || i > 0 && nums[i] == nums[i - 1] && !visited[i]) {
                continue;  // path里已经收录的元素，直接跳过
            }
            visited[i] = true;
            path.emplace_back(nums[i]);  //# 做选择
            backtrack(nums, visited);
            path.pop_back();     //# 撤销选择
            visited[i] = false;  //将该选择再加入选择列表
        }
    }

   public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<bool> visited(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtrack(nums, visited);
        return result;
    }
};