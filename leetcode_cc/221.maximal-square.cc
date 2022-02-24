#include <vector>
using namespace std;

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int res = 0;
    int row = matrix.size(), col = matrix[0].size();
    //  dp(i,j) 表示以 (i,j) 为右下角，且只包含 1 的正方形的边长最大值
    vector<vector<int>> dp(row, vector<int>(col));
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (matrix[i][j] == '1') {
          if (i == 0 || j == 0) {
            dp[i][j] = 1;
          } else {
            dp[i][j] =
                min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
          }
          res = max(res, dp[i][j]);
        }
      }
    }
    return res * res;
  }
};