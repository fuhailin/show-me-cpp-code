#include <iostream>
#include <vector>
using namespace std;

class Solution {
    vector<vector<int>> memo;
    int dfs(int start, int end) {
        if (start >= end) {
            return 0;
        }
        if (memo[start][end] != 0) {
            return memo[start][end];
        }
        int ans = INT_MAX;
        for (int i = start; i <= end; i++) {
            ans = min(ans, max(dfs(start, i - 1), dfs(i + 1, end)) + i);
        }
        return memo[start][end] = ans;
        // return ans;
    }

   public:
    // int getMoneyAmount_dfs(int n) {
    //     memo.resize(n + 1, vector<int>(n + 1));
    //     return dfs(1, n);
    // }
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 2, vector<int>(n + 2));
        int j, _min;
        for (int len = 2; len <= n; len++) {
            for (int i = 1; i <= n - len + 1; i++) {
                j = i + len - 1;
                _min = INT_MAX;
                for (int k = i; k <= j; k++) {
                    _min = min(_min, max(dp[i][k - 1], dp[k + 1][j]) + k);
                }
                dp[i][j] = _min;
            }
        }
        return dp[1][n];
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.getMoneyAmount(10);
    cout << "res: " << res << endl;
    return 0;
}
