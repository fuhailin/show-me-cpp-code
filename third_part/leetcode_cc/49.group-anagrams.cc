#include "bits/stdc++.h"

class Solution {
   public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> memo;
        for (string &text : strs) {
            string tmp(text);
            sort(tmp.begin(), tmp.end());
            memo[tmp].emplace_back(text);
        }
        for (auto &[key, value] : memo) {
            res.emplace_back(value);
        }
        return res;
    }
};