#include <limits.h>

#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int coin : coins) {
            //完全背包，必须正序遍历
            for (int i = coin; i <= amount; i++) {
                if (dp[i - coin] != INT_MAX) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        if (dp[amount] == INT_MAX) return -1;
        return dp[amount];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 2, 5};
    int res = so.coinChange(test, 100);
    cout << "res: " << res << endl;
    return 0;
}
