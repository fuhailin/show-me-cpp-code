#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n < 2) {
            return s;
        }
        // dp[i][j] 表示 s[i..j] 是否是回文串
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int maxLen = 1;
        int begin = 0;
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
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }
                // 只要 dp[i][j] == true 成立，就表示子串 s[i..L] 是回文，此时记录回文长度和起始位置
                if (dp[i][j] && j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }

        return s.substr(begin, maxLen);
    }
};

TEST(LeetCode, 最长回文子串) {
    Solution s;
    {
        std::vector<string> input = {"babad", "cbbd", "a", "ac"};
        std::vector<string> result = {"bab", "bb", "a", "a"};
        for (int i = 0; i < input.size(); ++i) {
            string ret = s.longestPalindrome(input[i]);
            EXPECT_EQ(ret, result[i]);
        }
    }
}