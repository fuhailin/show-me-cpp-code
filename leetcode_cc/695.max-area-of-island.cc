#include <iostream>
#include <vector>
using namespace std;

class Solution {
  int ROW, COL;
  vector<vector<bool>> visited;

  int dfs(vector<vector<int>>& grid, int x, int y) {
    if (x < 0 || x >= ROW || y < 0 || y >= COL || visited[x][y] ||
        grid[x][y] == 0) {
      return 0;
    }
    visited[x][y] = true;

    return dfs(grid, x + 1, y) + dfs(grid, x - 1, y) + dfs(grid, x, y + 1) +
           dfs(grid, x, y - 1) + 1;
  }

 public:
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    ROW = grid.size();
    COL = grid[0].size();

    visited.resize(ROW, vector<bool>(COL, false));
    int res = 0, areas = 0;
    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (grid[i][j] == 1 && !visited[i][j]) {
          res = max(dfs(grid, i, j), res);
        }
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<vector<int>> test = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                              {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                              {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                              {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                              {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}

  };
  int res = so.maxAreaOfIsland(test);
  cout << res << endl;
  return 0;
}