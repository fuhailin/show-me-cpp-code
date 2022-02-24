#include <string>
#include <vector>
using namespace std;

class Solution {
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    bool backtracking(vector<vector<char>>& board, string& word, int idx, vector<vector<bool>>& visited, int x, int y) {
        if (idx == word.size() - 1) {
            return true;
        }
        for (pair<int, int> dir : directions) {
            int next_x = dir.first + x;
            int next_y = dir.second + y;
            if (next_x >= 0 && next_x < board.size() && next_y >= 0 && next_y < board[0].size() && !visited[next_x][next_y] && board[next_x][next_y] == word[idx + 1]) {
                visited[next_x][next_y] = true;
                if (backtracking(board, word, idx + 1, visited, next_x, next_y)) return true;
                visited[next_x][next_y] = false;
            }
        }
        return false;
    }

   public:
    bool exist(vector<vector<char>>& board, string word) {
        int rows = board.size();
        int cols = board[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                if (board[x][y] == word[0]) {
                    visited[x][y] = true;
                    if (backtracking(board, word, 0, visited, x, y)) {
                        return true;
                    }
                    visited[x][y] = false;
                }
            }
        }
        return false;
    }
};