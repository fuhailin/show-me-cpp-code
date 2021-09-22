#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    // bool isSubsequence(char *s, char *t) {
    //     while (*s && *t) {
    //         if (*s == *t) {
    //             s++;
    //         }
    //         t++;
    //     }
    //     return !*s;
    // }
    bool isSubsequence(string s, string t) {
        vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= t.size(); ++j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        return dp[s.size()][t.size()] == s.size();
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    bool res = so.isSubsequence("axc", "ahbgdc");
    cout << "res: " << boolalpha << res << endl;
    return 0;
}
