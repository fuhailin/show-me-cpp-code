#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    int row = matrix.size(), col = matrix[0].size();
    vector<vector<int>> left(row, vector<int>(col, 0));
    for (int j = 0; j < col; j++) {
      for (int i = 0; i < row; i++) {
        if (matrix[i][j] == '1') {
          left[i][j] = (i == 0 ? 0 : left[i - 1][j]) + 1;
        }
      }
    }

    int res = 0;
    for (int i = 0; i < row; i++) {
      //单调栈
      int idx = 0;
      stack<int> stk;
      while (idx < col) {
        if (stk.empty() || left[i][idx] >= left[i][stk.top()]) {
          stk.push(idx);
          idx++;
        } else {
          int cur = stk.top();
          stk.pop();
          if (stk.empty()) {
            res = max(res, left[i][cur] * idx);
          } else {
            res = max(res, left[i][cur] * (idx - stk.top() - 1));
          }
        }
      }
      while (!stk.empty()) {
        int cur = stk.top();
        stk.pop();
        if (stk.empty()) {
          res = max(res, left[i][cur] * idx);
        } else {
          res = max(res, left[i][cur] * (idx - stk.top() - 1));
        }
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  //   vector<vector<char>> test = {{'1', '0', '1', '0', '0'},
  //                                {'1', '0', '1', '1', '1'},
  //                                {'1', '1', '1', '1', '1'},
  //                                {'1', '0', '0', '1', '0'}};
  vector<vector<char>> test = {
      {'1'},
  };

  int res = so.maximalRectangle(test);
  cout << res << endl;
  return 0;
}