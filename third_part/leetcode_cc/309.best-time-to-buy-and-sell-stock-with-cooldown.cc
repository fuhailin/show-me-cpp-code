#include <vector>
using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, 0));

        for (int i = 0; i < n; ++i) {
            if (i == 0) {
                dp[i][0] = 0;
                dp[i][1] = -prices[0];
            } else if (i == 1) {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
                dp[i][1] = max(dp[i - 1][0] - prices[i], dp[i - 1][1]);
            } else {
                dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
                dp[i][1] = max(dp[i - 2][0] - prices[i], dp[i - 1][1]);
            }
        }
        return dp[n - 1][0];
    }
};