#include <iostream>
#include <vector>
using namespace std;

class Solution {
  const vector<pair<int, int>> dirs = {
      {0, -1}, {0, 1}, {1, 0}, {-1, 0}};  //下、上、右、左
  vector<vector<bool>> visited;
  int ROW, COL;
  void dfs(vector<vector<char>>& grid, int x, int y) {
    if (x < 0 || x >= ROW || y < 0 || y >= COL || visited[x][y] ||
        grid[x][y] == '0') {
      return;
    }
    visited[x][y] = true;
    for (auto dir : dirs) {
      dfs(grid, x + dir.first, y + dir.second);
    }
  }

 public:
  int numIslands(vector<vector<char>>& grid) {
    ROW = grid.size();
    COL = grid[0].size();
    visited.resize(ROW, vector<bool>(COL, false));
    int res = 0;
    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (grid[i][j] == '1' && !visited[i][j]) {
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
  //   vector<vector<char>> test = {{'1', '1', '1', '1', '0'},
  //                                {'1', '1', '0', '1', '0'},
  //                                {'1', '1', '0', '0', '0'},
  //                                {'0', '0', '0', '0', '0'}};

  vector<vector<char>> test = {{'1', '1', '0', '0', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '1', '0', '0'},
                               {'0', '0', '0', '1', '1'}};
  int res = so.numIslands(test);
  cout << res << endl;
  return 0;
}