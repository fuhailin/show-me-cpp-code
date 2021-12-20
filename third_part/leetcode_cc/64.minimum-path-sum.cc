#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int minPathSum(vector<vector<int>> &grid) {
    const int n = grid.size();
    const int m = grid[0].size();
    vector<int> dp(m);
    dp[0] = grid[0][0];
    for (int i = 1; i < m; i++) {
      dp[i] = dp[i - 1] + grid[0][i];
    }

    for (int i = 1; i < n; i++) {
      dp[0] += grid[i][0];
      for (int j = 1; j < m; j++) {
        dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
      }
    }
    return dp[m - 1];
  }
};

int main(int argc, const char **argv) {
  Solution so;
    vector<vector<int>> test = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
//   vector<vector<int>> test = {{1, 2, 3}, {4, 5, 6}};
  int res = so.minPathSum(test);
  cout << res << endl;
  return 0;
}