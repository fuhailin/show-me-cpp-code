#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    int missingNumber(vector<int>& nums) {
        int xorres = 0;
        for (auto num : nums) {
            xorres = xorres xor num;
        }
        for (int i = 0; i <= nums.size(); i++) {
            xorres = xorres xor i;
        }
        return xorres;
    }
};