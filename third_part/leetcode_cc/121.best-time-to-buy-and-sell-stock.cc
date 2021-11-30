#include <vector>
using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> dp(n, 0);
        dp[0] = prices[0];

        int res = 0;
        for (int i = 1; i < n; ++i) {
            res = max(res, prices[i] - dp[i - 1]);
            dp[i] = min(dp[i - 1], prices[i]);
        }
        return res;
    }
};