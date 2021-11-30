#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;
    void backtracking(vector<int>& nums, int idx, vector<bool>& visited) {
        res.emplace_back(path);
        for (int i = idx; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1] && !visited[i - 1]) {
                continue;
            }
            visited[i] = true;
            path.emplace_back(nums[i]);  //# 做选择
            backtracking(nums, i + 1, visited);
            path.pop_back();  //# 撤销选择
            visited[i] = false;
        }
    }

   public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        vector<bool> visited(n, false);
        sort(nums.begin(), nums.end());
        backtracking(nums, 0, visited);
        return res;
    }
};