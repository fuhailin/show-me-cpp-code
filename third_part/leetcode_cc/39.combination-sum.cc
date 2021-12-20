
#include <vector>
using namespace std;

class Solution {
    vector<int> path;
    vector<vector<int>> res;
    void backtracking(vector<int>& candidates, int target, int idx) {
        if(target < 0) return;//递归边界
        if(target == 0) {
            res.emplace_back(path);//记录答案
            return;
        }
        for(int i = idx; i < candidates.size(); i++) {
            if(candidates[i] <= target) {
                path.push_back(candidates[i]);//加入路径数组中
                backtracking(candidates, target - candidates[i], i);// 因为可以重复使用，所以还是i
                path.pop_back();//回溯，恢复现场
            }
        }
    }

   public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtracking(candidates, target, 0);
        return res;
    }
};