#include "bits/stdc++.h"

class Solution {
   public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> hashmap1, hashmap2;
        for (char &x : ransomNote) {
            hashmap1[x]++;
        }
        for (char &x : magazine) {
            hashmap2[x]++;
        }

        for(auto &[key, value] : hashmap1) {
            if(value > hashmap2[key]) {
                return false;
            }
        }
        return true;
    }
};