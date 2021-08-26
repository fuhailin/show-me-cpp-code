
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int>& candidates, int target, int startIndex) {
        if (0 == target) {
            result.emplace_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && candidates[i] <= target; i++) {
            // 要对同一树层使用过的元素进行跳过
            if (i > startIndex && candidates[i] == candidates[i - 1]) {
                continue;
            }
            path.emplace_back(candidates[i]);
            backtracking(candidates, target - candidates[i], i + 1);  // 和39.组合总和的区别1，这里是i+1，每个数字在每个组合中只能使用一次
            path.pop_back();
        }
    }

   public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        // 首先把给candidates排序，让其相同的元素都挨在一起。
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0);
        return result;
    }
};
