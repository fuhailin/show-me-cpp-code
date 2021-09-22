#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));
        for (int i = 0; i < n; i++) {
            for (int j = k; j >= 1; --j) {
                if (i == 0) {
                    dp[i][j][0] = 0;
                    dp[i][j][1] = -prices[i];
                } else {
                    dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                    dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
                }
            }
        }
        return dp[n - 1][k][0];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 2, 4, 2, 5, 7, 2, 4, 9, 0};
    int res = so.maxProfit(4, test);
    cout << "res: " << res << endl;
    return 0;
}
