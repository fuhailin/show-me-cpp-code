// { Driver Code Starts
#include "bits/stdc++.h"
using namespace std;

// } Driver Code Ends

class Solution {
   public:
    //Function to return max value that can be put in knapsack of capacity W.
    int knapSack(int W, int wt[], int val[], int n) {
        // dp[i][j]前i个物品放入承重j的背包所得最大价值
        vector<vector<int>> dp(n, vector<int>(W + 1, 0));
        // 承重0的背包最大价值为0
        for (int i = 0; i < n; ++i) {
            dp[i][0] = 0;
        }
        // 初始化第0件物品放入承重j的背包最大价值
        for (int j = 0; j <= W; ++j) {
            if (j >= wt[0]) {
                dp[0][j] = val[0];
            }
        }

        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= W; j++) {
                if (j < wt[i]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - wt[i]] + val[i]);
                }
            }
        }
        return dp[n - 1][W];
    }
};

// { Driver Code Starts.

int main() {
    //taking total testcases
    int t;
    cin >> t;
    while (t--) {
        //reading number of elements and weight
        int n, w;
        cin >> n >> w;

        int val[n];
        int wt[n];

        //inserting the values
        for (int i = 0; i < n; i++)
            cin >> val[i];

        //inserting the weights
        for (int i = 0; i < n; i++)
            cin >> wt[i];
        Solution ob;
        //calling method knapSack()
        cout << ob.knapSack(w, wt, val, n) << endl;
    }
    return 0;
}  // } Driver Code Ends