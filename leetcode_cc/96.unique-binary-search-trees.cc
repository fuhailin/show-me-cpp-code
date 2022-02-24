#include <iostream>
#include <vector>

#include "include/TreeNode.h"
using namespace std;

class Solution {
   public:
    int numTrees(int n) {
        vector<int> dp(n, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[i] += dp[j] * dp[i - j - 1];
            }
        }
        return dp[n];
    }
};