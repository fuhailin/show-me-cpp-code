#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(3, vector<int>(2, 0)));
        for (int i = 0; i < n; i++) {
            for (int j = 2; j >= 1; --j) {
                if (i == 0) {
                    dp[i][j][0] = 0;
                    dp[i][j][1] = -prices[i];
                } else {
                    dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                    dp[i][j][1] = max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
                }
            }
        }
        return max(dp[n - 1][2][0], max(dp[n - 1][1][0], dp[n - 1][0][0]));
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {3, 3, 5, 0, 0, 3, 1, 4};
    int res = so.maxProfit(test);
    cout << "res: " << res << endl;
    return 0;
}