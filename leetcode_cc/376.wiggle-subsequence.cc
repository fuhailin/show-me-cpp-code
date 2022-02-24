
#include "bits/stdc++.h"
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums)
    {
        int n = nums.size();
        if (n < 2)
            return n;
        int preDiff = 0, curDiff, res = 1;
        for (int i = 1; i < nums.size(); i++) {
            curDiff = nums[i] - nums[i - 1];
            if (preDiff <= 0 && curDiff > 0 || preDiff >= 0 && curDiff < 0) {
                res++;
                preDiff = curDiff;
            }
        }
        return res;
    }
};

int main(int argc, char const* argv[])
{
    Solution so;
    vector<int> test = {};
    return 0;
}
