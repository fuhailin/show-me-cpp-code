#include "bits/stdc++.h"

class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {

        vector<int> res;
        sort(nums.begin(), nums.end());
        int a = std::upper_bound(nums.begin(), nums.end(), target) - nums.begin();
        int b = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
        for(int i = b; i < a; i++) {
            res.push_back(i);
        }
        return res;
    }
};


int main(int argc, char const *argv[])
{
    Solution so;
    vector<int> test = {1,2,5,2,3};
    vector<int> res = so.targetIndices(test, 2);

    return 0;
}
