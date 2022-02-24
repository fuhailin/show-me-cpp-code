#include <string>
#include <vector>
using namespace std;

class Solution {
    bool isValid(vector<vector<char>>& board, int x, int y, char num) {
        for (int i = 0; i < 9; ++i) {
            if (board[i][y] == num) {
                return false;
            }
        }
        for (int j = 0; j < 9; ++j) {
            if (board[x][j] == num) {
                return false;
            }
        }
        int startRow = (x / 3) * 3;
        int startCol = (y / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++) {
            for (int j = startCol; j < startCol + 3; j++) {
                if (board[i][j] == num) return false;
            }
        }
        return true;
    }
    bool backtracking(vector<vector<char>>& board) {
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) {
                if (board[x][y] != '.') continue;
                for (char num = '1'; num <= '9'; num++) {
                    if (isValid(board, x, y, num)) {
                        board[x][y] = num;
                        if (backtracking(board)) return true;
                        board[x][y] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }

   public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};