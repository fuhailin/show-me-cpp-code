#include "bits/stdc++.h"

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set1(nums1.begin(), nums1.end()), set2(nums2.begin(), nums2.end());
        vector<int> res;
        for(int x : set1) {
            if(set2.find(x) != set2.end()) {
                res.push_back(x);
            }
        }
        return res;
    }
};