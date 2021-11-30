#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        //dp[i]表示容量为i的背包有几种组合方式
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int& coin : coins) {
            for (int i = coin; i <= amount; ++i) {
                dp[i] += dp[i - coin];
            }
        }
        return dp[amount];
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 2, 5};
    int res = so.change(5, test);
    cout << "result: " << res << endl;
    return 0;
}
