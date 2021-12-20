#include <vector>
using namespace std;

class Solution {
    vector<int> path;
    vector<vector<int>> res;
    void backtracking(const int &n, const int &k, int index) {
        // 剪枝操作，剩余可选元素都不够所需总数则可停止搜索
        if ((path.size() + n - index + 1) < k) return;
        if (path.size() == k) {
            res.emplace_back(path);
            return;
        }
        path.emplace_back(index);
        backtracking(n, k, index + 1);
        path.pop_back();
        backtracking(n, k, index + 1);
    }

   public:
    vector<vector<int>> combine(int n, int k) {
        backtracking(n, k, 1);
        return res;
    }
};