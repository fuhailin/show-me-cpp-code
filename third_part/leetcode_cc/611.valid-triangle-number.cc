#include <vector>
#include <algorithm>

class Solution {
public:
    int triangleNumber(vector<int>& nums) {
        int n = nums.size();
        if (n < 3){
            return 0;
        }
        int res = 0;
        sort(nums.begin(), nums.end());
        for(int k = n-1;k>1;--k){
            int i = 0, j = k-1;
            while (i< j)
            {
                if(nums[i] + nums[j] > nums[k]){
                    res += j - i;
                    --j;
                } else {
                    ++i;
                }
            }
        }
        return res;
    }
};