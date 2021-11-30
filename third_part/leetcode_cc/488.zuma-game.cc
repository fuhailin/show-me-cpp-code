#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
    unordered_map<char, int> freq;
    unordered_map<string, int> cache;

   public:
    // squezz the string by removing all 3+ bolls
    string squezz(string line) {
        int i = 0;
        while (i < line.size()) {
            int j = i;
            while (j < line.size() && line[i] == line[j]) {
                j++;
            }
            if ((j - i) >= 3) {
                line = line.substr(0, i) + line.substr(j);
                i = 0;
            } else {
                i++;
            }
        }
        return line;
    }

    int backtracking(string &board) {
        if (cache.count(board)) return cache[board];
        int r = INT_MAX;
        if (board.length() == 0) {  // base case => we have removed all the balls from table
            r = 0;
            cache[board] = r;
            return r;
        }

        for (int i = 0; i < board.length(); i++) {              // try inserting a ball from hand at every position on row of balls
            for (auto &it : freq) {                             // try all the balls at every position
                if (it.second > 0) {                            // only if the frequency is more than 0, skipping this line will lead to runtime error
                    board.insert(board.begin() + i, it.first);  // insert ball at ith index
                    it.second--;                                // update the frequency of ball

                    string newStr = squezz(board);     // remove groups of 3 or more if possible
                    int steps = backtracking(newStr);  // recursively call the function for the new string board
                    if (steps != -1) {                 // steps will be -1 if we can't remove all the balls using this combination
                        r = min(r, steps + 1);
                    }
                    it.second++;                     // restore the frequency
                    board.erase(board.begin() + i);  // remove the ball from this position to try next combination
                }
            }
        }
        if (r == INT_MAX) r = -1;  // we can't remove all the balls
        cache[board] = r;
        return r;
    }

    int findMinStep(string board, string hand) {
        for (char x : hand) {
            freq[x]++;
        }
        return backtracking(board);
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    cout << so.findMinStep("RRYGGYYRRYGGYYRR", "GGBBB") << endl;
    // cout << so.squezz("WBRRRBBW") << endl;
    return 0;
}
