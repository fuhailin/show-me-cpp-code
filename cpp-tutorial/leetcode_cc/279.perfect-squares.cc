#include <math.h>

#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numSquares(int n) {
        // int len = sqrt(n);
        // vector<int> dp(n + 1, INT_MAX);
        // dp[0] = 0;
        // dp[1] = 1;

        // for (int i = 2; i <= n; ++i) {
        //     for (int j = 1; pow(j, 2) <= i; j++) {
        //         dp[i] = min(dp[i], dp[i - pow(j, 2)] + 1);
        //     }
        // }
        // return dp[n];
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i * i <= n; i++) {  // 遍历物品
            for (int j = 1; j <= n; j++) {  // 遍历背包
                if (j - i * i >= 0) {
                    dp[j] = min(dp[j - i * i] + 1, dp[j]);
                }
            }
        }
        return dp[n];
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.numSquares(13);
    cout << "res: " << res << endl;
    return 0;
}
