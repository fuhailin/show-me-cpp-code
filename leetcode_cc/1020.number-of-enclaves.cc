#include <iostream>
#include <vector>
using namespace std;

class Solution {
  const vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  int m, n;
  vector<vector<bool>> visited;

  void dfs(const vector<vector<int>>& grid, int row, int col) {
    if (row < 0 || row >= m || col < 0 || col >= n || grid[row][col] == 0 ||
        visited[row][col]) {
      return;
    }
    visited[row][col] = true;
    for (auto& dir : dirs) {
      dfs(grid, row + dir[0], col + dir[1]);
    }
  }

 public:
  int numEnclaves(vector<vector<int>>& grid, int row, int col) {
    this->m = grid.size();
    this->n = grid[0].size();
    this->visited = vector<vector<bool>>(m, vector<bool>(n, false));
    // 左右边界
    for (int i = 0; i < m; i++) {
      dfs(grid, i, 0);
      dfs(grid, i, n - 1);
    }
    // 上下边界
    for (int j = 1; j < n; j++) {
      dfs(grid, 0, j);
      dfs(grid, m - 1, j);
    }

    int enclaves = 0;
    for (int i = 1; i < m - 1; i++) {
      for (int j = 1; j < n - 1; j++) {
        if (grid[i][j] == 1 && !visited[i][j]) {
          enclaves++;
        }
      }
    }
    return enclaves;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<vector<int>> grid = {
      {0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
  int res = so.numEnclaves(grid);
  cout << "res: " << res << endl;
  return 0;
}