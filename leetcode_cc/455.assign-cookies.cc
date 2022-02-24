#include "bits/stdc++.h"

class Solution {
   public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int res = 0;
        int i = 0, j = 0;
        while (i < s.size() && j < g.size()) {
            if (s[i] >= g[j]) {
                res++;
                i++;
                j++;
            } else {
                i++;
            }
        }
        return res;
    }
};