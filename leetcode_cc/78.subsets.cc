#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;
    void backtracking(vector<int>& nums, int idx) {
        res.emplace_back(path);
        for (int i = idx; i < nums.size(); i++) {
            path.emplace_back(nums[i]);  //# 做选择
            backtracking(nums, i + 1);
            path.pop_back();  //# 撤销选择
        }
    }

   public:
    vector<vector<int>> subsets(vector<int>& nums) {
        backtracking(nums, 0);
        return res;
    }
};