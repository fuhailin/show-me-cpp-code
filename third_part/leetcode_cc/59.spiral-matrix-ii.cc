#include "bits/stdc++.h"

class Solution {
   public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n));
        int u = 0, d = n - 1, l = 0, r = n - 1, num = 1;
        while (true) {
            for (int i = l; i <= r; i++) {
                matrix[u][i] = num++;
            }
            if (++u > d) break;
            for (int i = u; i <= d; i++) {
                matrix[i][r] = num++;
            }
            if (--r < l) break;
            for (int i = r; i >= l; --i) {
                matrix[d][i] = num++;
            }
            if (--d < u) break;
            for (int i = d; i >= u; --i) {
                matrix[i][l] = num++;
            }
            if (++l > r) break;
        }
        return matrix;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    auto res = so.generateMatrix(n);
    return 0;
}
