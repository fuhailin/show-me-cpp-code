#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1, mid;
        while (left <= right) {
            mid = left + ((right - left) >> 1);
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        if (nums[mid] > target)
            return mid;
        else
            return mid + 1;
    }
};


int main(int argc, char const *argv[])
{
    vector<int> test = {1, 3, 5, 6};
    Solution solu;
    int res = solu.searchInsert(test, 2);
    cout << res << endl;
    return 0;
}
