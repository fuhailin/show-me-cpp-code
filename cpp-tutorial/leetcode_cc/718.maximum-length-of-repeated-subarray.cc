#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size(), res = 0;
        if (n1 == 0 || n2 == 0) return 0;
        vector<vector<int>> dp(n1, vector<int>(n2, 0));
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (nums1[i] == nums2[j]) {
                    if (i == 0 || j == 0) {
                        dp[i][j] = 1;
                    } else {
                        dp[i][j] = dp[i - 1][j - 1] + 1;
                    }
                }
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> A{1, 2, 3, 2, 1}, B{3, 2, 1, 4, 7};
    int res = so.findLength(A, B);
    cout << "res: " << res << endl;
    return 0;
}
