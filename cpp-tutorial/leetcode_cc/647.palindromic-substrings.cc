#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int countSubstrings(string s) {
        int res = 0;
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), false));
        for (int i = 0; i < s.size(); ++i) {
            for (int j = 0; j <= i; ++j) {
                if (s[i] == s[j]) {
                    if (i - j <= 1) {
                        res++;
                        dp[i][j] = true;
                    } else if (dp[i - 1][j + 1]) {
                        res++;
                        dp[i][j] = true;
                    }
                }
            }
        }
        return res;
    }
};