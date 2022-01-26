#include "bits/stdc++.h"

class Solution {
   public:
    string replaceSpace(string s) {
        int emptyNum = 0;
        int n = s.size();
        for (char& c : s) {
            if (c == ' ') {
                emptyNum++;
            }
        }
        s.resize(n + 2 * emptyNum);
        int idx = s.size() - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == ' ') {
                s[idx--] = '0';
                s[idx--] = '2';
                s[idx--] = '%';
            } else {
                s[idx--] = s[i];
            }
        }
        return s;
    }
};