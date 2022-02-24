#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    void nextPermutation(vector<int>& nums) {
        int i;
        for (i = nums.size() - 2; i >= 0; --i) {
            if (nums[i + 1] > nums[i]) {
                break;
            }
        }
        if (i == -1) {
            reverse(nums.begin(), nums.end());
        } else {
            for (int j = nums.size() - 1; j > i; --j) {
                if (nums[j] > nums[i]) {
                    swap(nums[i], nums[j]);
                    reverse(nums.begin() + i + 1, nums.end());
                    break;
                }
            }
        }
    }
};