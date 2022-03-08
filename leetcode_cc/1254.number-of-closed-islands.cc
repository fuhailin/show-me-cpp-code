#include <iostream>
#include <vector>
using namespace std;

class Solution {
  const vector<pair<int, int>> dirs = {
      {0, -1}, {0, 1}, {1, 0}, {-1, 0}};  //下、上、右、左
  int ROW, COL;
  vector<vector<bool>> visited;
  void dfs(vector<vector<int>>& grid, int x, int y) {
    if (x < 0 || x >= ROW || y < 0 || y >= COL || visited[x][y] ||
        grid[x][y] == 1) {
      return;
    }
    visited[x][y] = true;
    for (auto dir : dirs) {
      dfs(grid, x + dir.first, y + dir.second);
    }
  }

 public:
  int closedIsland(vector<vector<int>>& grid) {
    ROW = grid.size();
    COL = grid[0].size();
    visited.resize(ROW, vector<bool>(COL, false));
    int res = 0;

    for (int j = 0; j < COL; j++) {
      // 把靠上边的岛屿淹掉
      dfs(grid, 0, j);
      // 把靠下边的岛屿淹掉
      dfs(grid, ROW - 1, j);
    }
    for (int i = 0; i < ROW; i++) {
      // 把靠左边的岛屿淹掉
      dfs(grid, i, 0);
      // 把靠右边的岛屿淹掉
      dfs(grid, i, COL - 1);
    }

    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (grid[i][j] == 0 && !visited[i][j]) {
          res++;
          dfs(grid, i, j);
        }
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<vector<int>> test = {{1, 1, 1, 1, 1, 1, 1, 0},
                              {1, 0, 0, 0, 0, 1, 1, 0},
                              {1, 0, 1, 0, 1, 1, 1, 0},
                              {1, 0, 0, 0, 0, 1, 0, 1},
                              {1, 1, 1, 1, 1, 1, 1, 0}};
  int res = so.closedIsland(test);
  cout << res << endl;
  return 0;
}