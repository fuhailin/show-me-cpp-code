#include "bits/stdc++.h"

class Solution {
   public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> memo;
        int res = 0;
        for (int i : nums1) {
            for (int j : nums2) {
                memo[i + j]++;
            }
        }

        for (int i : nums3) {
            for (int j : nums4) {
                res += memo[-i - j];
            }
        }
        return res;
    }
};