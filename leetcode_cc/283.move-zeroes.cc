#include <iostream>
#include <vector>

class Solution {
   public:
    void moveZeroes(vector<int>& nums) {
        int slow = 0, fast = 0;
        while (fast < nums.size()) {
            if (nums[fast] != 0) {
                nums[slow] = nums[fast];
                slow++;
            }
            fast++;
        }
        while (slow < nums.size()) {
            nums[slow++] = 0;
        }
    }
};