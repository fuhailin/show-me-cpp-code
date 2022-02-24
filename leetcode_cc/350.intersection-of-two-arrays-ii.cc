#include "bits/stdc++.h"

class Solution {
   public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
        if (nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }
        unordered_map<int, int> memo1, memo2;
        for (auto &x : nums1) {
            memo1[x]++;
        }

        for (auto &x : nums2) {
            memo2[x]++;
        }

        vector<int> res;
        for (auto &[key, value] : memo1) {
            if (memo2.count(key)) {
                for (int i = 0; i < min(value, memo2[key]); i++) {
                    res.push_back(key);
                }
            }
        }
        return res;
    }
};