
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> res;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int idx) {
        if(idx == candidates.size()){
            return;
        }
        if (target == 0) {
            res.emplace_back(path);
            return;
        }
        backtracking(candidates, target, idx + 1);
        if (target - candidates[idx] >= 0) {
            path.emplace_back(candidates[idx]);
            backtracking(candidates, target - candidates[idx], idx);
            path.pop_back();
        }
    }

   public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtracking(candidates, target, 0);
        return res;
    }
};