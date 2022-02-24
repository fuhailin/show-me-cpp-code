#include "bits/stdc++.h"

class Solution {
   public:
    int removeElement(vector<int>& nums, int val) {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
            if (val != nums[fastIndex]) {
                nums[slowIndex++] = nums[fastIndex];
            }
        }
        return slowIndex;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {3, 2, 2, 3};
    int res = so.removeElement(test, 3);
    LOG(INFO) << "res: " << test;
    return 0;
}
