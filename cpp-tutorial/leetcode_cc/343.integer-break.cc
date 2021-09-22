#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, 0);
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 2; j < i; ++j) {
                dp[i] = max(j * (i - j), j * dp[i - j]);
            }
        }
        return dp[n];
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.integerBreak(10);
    cout << "res: " << res << endl;
    return 0;
}
