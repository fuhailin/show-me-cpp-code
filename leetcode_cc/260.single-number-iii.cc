#include "bits/stdc++.h"
class Solution {
   public:
    vector<int> singleNumber(vector<int>& nums) {
        int xnum = 0;
        for (int num : nums) {
            xnum ^= num;
        }
        int flag = xnum ^ (-xnum);
        return {0, 1};
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 2, 1, 3, 2, 5};
    vector<int> res = so.singleNumber(test);
    return 0;
}
