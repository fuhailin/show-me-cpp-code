
#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
   public:
    int longestPalindromeSubseq(string s) {
        int n = s.length();
        // dp[i][j] 表示 s[i..j] 是否是回文串
        vector<vector<int>> dp(n, vector<int>(n, 1));
        // 从短到长开始遍历
        for (int L = 2; L <= n; L++) {
            // 从左到右开始遍历
            for (int i = 0; i < n; i++) {
                int j = i + L - 1;
                if (j >= n) {
                    break;
                }
                if (s[i] == s[j]) {
                    if (j - i < 3) {
                        dp[i][j] = j - i + 1;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1] + 2;
                    }
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[0][s.size() - 1];
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.longestPalindromeSubseq("bbbab");
    cout << "res: " << res << endl;
    return 0;
}
