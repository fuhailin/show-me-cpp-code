#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    int longestCommonSubsequence(string text1, string text2) {
        int n1 = text1.size(), n2 = text2.size(), res = 0;
        if (n1 == 0 || n2 == 0) return 0;
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }
        return dp[n1][n2];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    string text1 = "abcde", text2 = "ace";
    int res = so.longestCommonSubsequence(text1, text2);
    cout << "res: " << res << endl;
    return 0;
}