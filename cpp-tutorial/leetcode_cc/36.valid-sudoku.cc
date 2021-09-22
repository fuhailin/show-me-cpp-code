#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int n = board.size();
        vector<vector<short>> cache(27, vector<short>(9, 0));
        short num;
        for (int x = 0; x < 9; ++x) {
            for (int y = 0; y < 9; ++y) {
                if (board[x][y] == '.') continue;
                num = board[x][y] - '1';
                if (++cache[x][num] > 1) return false;
                if (++cache[9 + y][num] > 1) return false;
                if (++cache[18 + x / 3 * 3 + y / 3 * 3][num] > 1) return false;
            }
        }
        return true;
    }
};