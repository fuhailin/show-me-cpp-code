#include <vector>
using namespace std;

class Solution {
   public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int n = values.size();
        int res;
        vector<int> dp(n, 0);
        dp[0] = values[0];
        for (int i = 1; i < n; ++i) {
            res = max(values[i] + i + dp[i-1], res);
            dp[i] = max(dp[i - 1], values[i] + i);
        }
        return res;
    }
};