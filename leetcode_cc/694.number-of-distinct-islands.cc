#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
  int ROW, COL;
  vector<vector<bool>> visited;
  unordered_set<string> res;

  void dfs(vector<vector<int>>& grid, int x, int y, string& path, char arrow) {
    if (x < 0 || x >= ROW || y < 0 || y >= COL || grid[x][y] == 0) {
      return;
    }
    grid[x][y] = 0;
    path.push_back(arrow);
    dfs(grid, x + 1, y, path, 'A');
    dfs(grid, x - 1, y, path, 'B');
    dfs(grid, x, y + 1, path, 'C');
    dfs(grid, x, y - 1, path, 'D');
    path.push_back(arrow - 10);
  }

 public:
  int numDistinctIslands(vector<vector<int>>& grid) {
    ROW = grid.size();
    COL = grid[0].size();

    visited.resize(ROW, vector<bool>(COL, false));
    for (int i = 0; i < ROW; i++) {
      for (int j = 0; j < COL; j++) {
        if (grid[i][j] == 1) {
          string _path = "";
          dfs(grid, i, j, _path, '6');
          res.insert(_path);
        }
      }
    }
    int len = res.size();
    return len;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  //   vector<vector<int>> test = {{1, 1, 1, 1, 0},
  //                                {1, 1, 0, 1, 0},
  //                                {1, 1, 0, 0, 0},
  //                                {0, 0, 0, 0, 0}};

  vector<vector<int>> test = {
      {1, 1, 1, 1, 0}, {1, 1, 0, 1, 0}, {1, 1, 0, 0, 0}, {0, 0, 0, 0, 0}};
  int res = so.numDistinctIslands(test);
  cout << res << endl;
  return 0;
}