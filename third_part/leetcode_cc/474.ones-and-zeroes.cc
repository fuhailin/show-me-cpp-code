#include <iostream>
#include <vector>

using namespace std;

class Solution {
    pair<int, int> countZeroAndOne(string &str) {
        int zeros = 0, ones = 0;
        for (char &c : str) {
            if (c == '0') {
                zeros++;
            } else {
                ones++;
            }
        }
        return {zeros, ones};
    }

   public:
    int findMaxForm(vector<string> &strs, int m, int n) {
        // m 个 0 和 n 个 1，两个0-1🎒
        // dp[i][j]：最多有i个0和j个1的strs的最⼤⼦集的⼤⼩为dp[i][j]
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (string &str : strs) {
            pair<int, int> counts = countZeroAndOne(str);
            int zeros = counts.first;
            int ones = counts.second;
            for (int j = m; zeros <= j; --j) {
                for (int k = n; ones <= k; --k) {
                    dp[j][k] = max(dp[j - zeros][k - ones] + 1, dp[j][k]);
                }
            }
        }
        return dp[m][n];
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    vector<string> test = {"10", "0001", "111001", "1", "0"};
    int res = so.findMaxForm(test, 5, 3);
    cout << "res: " << res << endl;
    return 0;
}
