#include <stack>
#include <string>
#include <vector>
using namespace std;

class Solution {
    vector<string> result;
    string path;

    void backtracking(int n, int left, int right) {
        if (left == n && right == n) {
            result.emplace_back(path);
            return;
        }
        if (left < n) {
            path.push_back('(');
            backtracking(n, left + 1, right);
            path.pop_back();
        }
        if (left > right) {
            path.push_back(')');
            backtracking(n, left, right + 1);
            path.pop_back();
        }
    }

   public:
    vector<string> generateParenthesis(int n) {
        if (n < 1) {
            return result;
        }
        backtracking(n, 0, 0);
        return result;
    }
};