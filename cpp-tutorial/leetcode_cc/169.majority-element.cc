#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int majorityElement(vector<int>& nums) {
        int res = -1;
        int count = 0;
        for (int& num : nums) {
            if (num == res) {
                count++;
            } else {
                if (count > 0) {
                    count--;
                } else {
                    res = num;
                    count = 1;
                }
            }
        }
        return res;
    }
};