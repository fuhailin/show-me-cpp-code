#include "bits/stdc++.h"

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        vector<int> res(nums.size());
        int i = right;
        while (left <= right)
        {
            int left_square = nums[left] * nums[left];
            int right_square = nums[right] * nums[right];
            if(left_square < right_square) {
                res[i] = right_square;
                right--;
            } else {
                res[i] = left_square;
                left++;
            }
            i--;
        }
        return res;
    }
};