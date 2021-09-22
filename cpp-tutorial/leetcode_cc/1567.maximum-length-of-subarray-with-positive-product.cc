#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> dpPos(n, 0);
        vector<int> dpNeg(n, 0);
        if (nums[0] > 0) {
            dpPos[0] = 1;
        } else if (nums[0] < 0) {
            dpNeg[0] = 1;
        }
        int res = dpPos[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > 0) {
                dpNeg[i] = dpNeg[i - 1] == 0 ? 0 : dpNeg[i - 1] + 1;
                dpPos[i] = dpPos[i - 1] + 1;
            } else if (nums[i] < 0) {
                dpNeg[i] = dpPos[i - 1] + 1;
                dpPos[i] = dpNeg[i - 1] == 0 ? 0 : dpNeg[i - 1] + 1;
            } else {
                dpPos[i] = 0;
                dpNeg[i] = 0;
            }
            res = max(res, dpPos[i]);
        }
        return res;
    }
};