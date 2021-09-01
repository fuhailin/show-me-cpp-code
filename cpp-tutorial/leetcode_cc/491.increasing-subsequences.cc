#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;

    void backtracking(vector<int>& nums, int idx) {
        if (path.size() >= 2) {
            res.emplace_back(path);
        }
        int used[201] = {0}; // 这里使用数组来进行去重操作，题目说数值范围[-100, 100]
        for (int i = idx; i < nums.size(); i++) {
            // 要对同一树层使用过的元素进行跳过
            if (!path.empty() && path.back() > nums[i] || used[nums[i] + 100] == 1) {
                continue;
            }
            used[nums[i] + 100] = 1; // 记录这个元素在本层用过了，本层后面不能再用了
            path.emplace_back(nums[i]);
            backtracking(nums, i + 1);  // 和39.组合总和的区别1，这里是i+1，每个数字在每个组合中只能使用一次
            path.pop_back();
        }
    }

   public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        int n = nums.size();
        vector<bool> visited(n, false);
        backtracking(nums, 0);
        return res;
    }
};