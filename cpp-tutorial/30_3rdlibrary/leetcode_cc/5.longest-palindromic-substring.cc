#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    string longestPalindrome(string s) {
        int N = s.length();
        vector<int> memo(N + 1, 0);
        return s;
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