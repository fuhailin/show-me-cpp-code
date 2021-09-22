#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        vector<bool> dp(n + 1);
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (auto& word : wordDict) {
                int sz = word.size();
                if (i - sz >= 0 && s.substr(i - sz, sz) == word)
                    dp[i] = dp[i] || dp[i - sz];
            }
        }
        return dp[n];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<string> wordDict = {"leet", "code"};
    bool res = so.wordBreak("leetcode", wordDict);
    cout << "res: " << res << endl;
    return 0;
}
