#include <iostream>
#include <unordered_map>
#include <vector>

#include "bits/stdc++.h"
using namespace std;

class Solution {
   public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> hashmap;
        for (int i = 0; i < nums.size(); i++) {
            if (hashmap.find(nums[i]) == hashmap.end()) {
                hashmap[target - nums[i]] = i;
            } else {
                return {i, hashmap[nums[i]]};
            }
        }
        return {-1, -1};
    }
};

int main(int argc, const char **argv) {
    Solution so;
    vector<int> test = {2, 7, 11, 15};
    vector<int> res = so.twoSum(test, 9);
    LOG(INFO) << "res: " << res;
    return 0;
}