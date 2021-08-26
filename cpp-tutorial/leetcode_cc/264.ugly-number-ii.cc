#include <iostream>
#include <set>
#include <vector>
using namespace std;

class Solution {
   public:
    int nthUglyNumber(int n) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        int p2 = 1, p3 = 1, p5 = 1;

        for (int i = 2; i <= n; ++i) {
            int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
            dp[i] = min(min(num2, num3), num5);
            if (dp[i] == num2) {
                ++p2;
            }
            if (dp[i] == num3) {
                ++p3;
            }
            if (dp[i] == num5) {
                ++p5;
            }
        }
        return dp[n];
    }
};

int main(int argc, char const *argv[]) {
    Solution s;
    int res = s.nthUglyNumber(10);
    cout << "res: " << res << endl;
    return 0;
}
