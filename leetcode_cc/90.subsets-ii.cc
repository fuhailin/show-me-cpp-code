#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;
    void backtracking(vector<int>& nums, int idx) {
        res.emplace_back(path);
        // if(idx >= nums.size()) return;
        for(int i = idx; i < nums.size(); i++) {
            if(i > idx && nums[i] == nums[i - 1]) continue;
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }

   public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return res;
    }
};