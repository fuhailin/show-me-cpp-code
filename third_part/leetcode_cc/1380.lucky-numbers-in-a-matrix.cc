#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> luckyNumbers(vector<vector<int>>& matrix) {
    int row = matrix.size(), col = matrix[0].size();
    vector<int> row_min(row, INT_MAX), col_max(col, INT_MIN);
    vector<int> res;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        row_min[i] = min(row_min[i], matrix[i][j]);
        col_max[j] = max(col_max[j], matrix[i][j]);
      }
    }

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (row_min[i] == col_max[j]) {
          res.emplace_back(row_min[i]);
        }
      }
    }
    return res;
  }
};