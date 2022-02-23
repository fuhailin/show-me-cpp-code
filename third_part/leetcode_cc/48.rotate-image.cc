#include <vector>
using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int i = 0, j = n - 1;
    // 上下翻转
    while (i < j) {
      swap(matrix[i], matrix[j]);
      i++;
      j--;
    }
    // 对角线翻转
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        swap(matrix[i][j], matrix[j][i]);
      }
    }
  }
};