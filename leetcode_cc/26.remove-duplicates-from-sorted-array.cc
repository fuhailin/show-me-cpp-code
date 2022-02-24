#include <iostream>
#include <vector>

#include "bits/stdc++.h"
using namespace std;

class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        int slow = 1;
        for (int fast = 1; fast < nums.size(); fast++) {
            if (nums[fast] != nums[slow - 1]) {
                nums[slow] = nums[fast];
                slow++;
            }
        }
        return slow;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int res = so.removeDuplicates(test);
    cout << "res: " << res << endl;
    LOG(INFO) << test;
    return 0;
}
