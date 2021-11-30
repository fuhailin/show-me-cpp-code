#include <iostream>
#include <vector>

#include "bits/stdc++.h"
using namespace std;

class Solution {
   public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;
        int slow = 2;
        for (int fast = 2; fast < n; fast++) {
            if (nums[fast] != nums[slow - 2]) {
                nums[slow] = nums[fast];
                slow += 1;
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