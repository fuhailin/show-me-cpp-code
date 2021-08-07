#include <string>
#include <vector>

class Solution {
    vector<string> result;
    string combination;
    void backtracking(int depth, int index) {
        if (depth == index) {
            result.emplace_back(combination);
            return;
        }

        for (auto each :) {
            combination;
            backtracking(depth - 1);
            combination;
        }
    }

   public:
    vector<string> generateParenthesis(int n) {
        if (n < 1) {
            return result;
        }
        backtracking(n, n);
    }
};