#include <vector>
using namespace std;

class Solution {
   private:
    vector<vector<int>> result;  // 存放结果集
    vector<int> path;            // 符合条件的结果
    void backtracking(int target, int k, int startIndex) {
        if (0 > target) {  // 剪枝操作
            return;        // 如果path.size() == k 但sum != targetSum 直接返回
        }
        if (path.size() == k) {
            if (0 == target) result.emplace_back(path);
            return;
        }
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) {  // 剪枝
            path.emplace_back(i);                                           // 处理
            backtracking(target - i, k, i + 1);                          // 注意i+1调整startIndex
            path.pop_back();                                             // 回溯
        }
    }

   public:
    vector<vector<int>> combinationSum3(int k, int n) {
        backtracking(n, k, 1);
        return result;
    }
};