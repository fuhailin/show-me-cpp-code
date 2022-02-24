#include "bits/stdc++.h"

class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> hashmap1, hashmap2;
        for(char &x : s) {
            hashmap1[x]++;
        }
        for(char &x : t) {
            hashmap2[x]++;
        }
        if(hashmap1.size() != hashmap2.size()) {
            return false;
        }
        for(auto &[key, value] : hashmap1) {
            if(value != hashmap2[key]) {
                return false;
            }
        }
        return true;
    }
};