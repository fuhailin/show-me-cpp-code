#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   private:
    vector<vector<int>> dp;
    vector<vector<string>> res;
    vector<string> path;
    int n;

   public:
    void backtracking(const string& s, int i) {
        if (i == n) {
            res.emplace_back(path);
            return;
        }
        for (int j = i; j < n; ++j) {
            if (!dp[i][j]) continue;
            path.emplace_back(s.substr(i, j - i + 1));
            backtracking(s, j + 1);
            path.pop_back();
        }
    }

    vector<vector<string>> partition(string s) {
        n = s.size();
        dp.assign(n, vector<int>(n, true));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
            }
        }

        backtracking(s, 0);
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    string test = "aba";
    bool res = so.isPalindrome(test);
    cout << "res: " << res << endl;
}
