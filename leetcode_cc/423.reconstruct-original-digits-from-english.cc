#include "bits/stdc++.h"

class Solution {
   public:
    string originalDigits(string s) {
        string res;
        unordered_map<char, int> memo;
        for (char c : s) {
            memo[c]++;
        }
        vector<int> cnt(10);
        cnt[0] = memo['z'];
        cnt[6] = memo['x'];
        cnt[2] = memo['w'];
        cnt[4] = memo['u'];
        cnt[8] = memo['g'];
        cnt[3] = memo['h'] - cnt[8];
        cnt[5] = memo['f'] - cnt[4];
        cnt[7] = memo['v'] - cnt[5];
        cnt[9] = memo['i'] - cnt[5] - cnt[6] - cnt[8];
        cnt[1] = memo['n'] - cnt[7] - 2 * cnt[9];

        for (int i = 0; i <= 9; i++) {
            for (int j = 1; j <= cnt[i]; j++) {
                res += ('0' + i);
            }
        }
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    string test = "nnei";
    string res = so.originalDigits(test);
    cout << res << endl;
    return 0;
}
