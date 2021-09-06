#include <vector>
using namespace std;

class Solution {
    int helper(vector<int>& nums, int start, int end) {
        int first = nums[start], second = max(nums[start], nums[start + 1]);
        for(int i = start + 2; i <= end; i++) {
            int tmp = max(first + nums[i], second);
            first = second;
            second = tmp;
        }
        return second;
    }

   public:
    int rob(vector<int>& nums) {
        int size = nums.size();
        if (size == 1) return nums[0];
        if (size == 2) return max(nums[0], nums[1]);
        return max(helper(nums, 0, size - 2), helper(nums, 1, size - 1));
    }
};