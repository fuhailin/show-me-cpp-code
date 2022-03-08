#include <iostream>
#include <vector>
using namespace std;

class Solution {
  const vector<pair<int, int>> dirs = {
      {0, -1}, {0, 1}, {1, 0}, {-1, 0}};  //下、上、右、左
  int ROW, COL;
  //   vector<vector<bool>> visited;

  void dfs(vector<vector<int>>& grid, int x, int y) {
    if (x < 0 || x >= ROW || y < 0 || y >= COL || grid[x][y] == 0) {
      return;
    }
    grid[x][y] = 0;
    for (auto dir : dirs) {
      dfs(grid, x + dir.first, y + dir.second);
    }
  }

 public:
  int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    ROW = grid1.size();
    COL = grid1[0].size();
    // visited.resize(ROW, vector<bool>(COL, false));

    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (grid1[i][j] == 0 && grid2[i][j] == 1) {
          // 这个岛屿肯定不是子岛，淹掉
          dfs(grid2, i, j);
        }
      }
    }

    int res = 0;
    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (grid2[i][j] == 1) {
          res++;
          dfs(grid2, i, j);
        }
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<vector<int>> grid1 = {{1, 1, 1, 0, 0},
                               {0, 1, 1, 1, 1},
                               {0, 0, 0, 0, 0},
                               {1, 0, 0, 0, 0},
                               {1, 1, 0, 1, 1}};
  vector<vector<int>> grid2 = {{1, 1, 1, 0, 0},
                               {0, 0, 1, 1, 1},
                               {0, 1, 0, 0, 0},
                               {1, 0, 1, 1, 0},
                               {0, 1, 0, 1, 0}};
  int res = so.countSubIslands(grid1, grid2);
  cout << res << endl;
  return 0;
}