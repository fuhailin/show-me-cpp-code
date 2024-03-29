#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int findDuplicate(vector<int>& nums) {
        int fast = 0, slow = 0;
        do {
            fast = nums[nums[fast]];
            slow = nums[slow];
        } while (fast != slow);

        slow = 0;
        while (slow != fast) {
            fast = nums[fast];
            slow = nums[slow];
        }
        return slow;
    }
};