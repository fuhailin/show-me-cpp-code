// #include <gtest/gtest.h>
// #include <unistd.h>

#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int mn = nums[n - 1], l = n;
        for (int i = n - 1; i >= 0; --i) {
            if (nums[i] > mn) {
                l = i;
            }
            mn = min(nums[i], mn);
        }
        int mx = nums[0], r = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] < mx) {
                r = i;
            }
            mx = max(nums[i], mx);
        }
        return max(r - l + 1, 0);
    }
};

int main(int argc, char const* argv[]) {
    Solution s;

    std::vector<int> input = {1, 3, 2, 2, 2};
    int res = s.findUnsortedSubarray(input);
    cout << "res: " << res << endl;
    return 0;
}
