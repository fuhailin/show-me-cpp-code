#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
        for (int i = 0; i <= word1.size(); ++i) {
            for (int j = 0; j <= word2.size(); ++j) {
                if (i == 0) {
                    dp[i][j] = j;
                } else if (j == 0) {
                    dp[i][j] = i;
                } else if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.minDistance("horse", "ros");
    cout << "res: " << res << endl;
    return 0;
}