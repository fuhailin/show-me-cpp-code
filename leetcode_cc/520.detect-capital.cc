#include <iostream>
#include <string>
using namespace std;

class Solution {
   public:
    bool detectCapitalUse(string word) {
        int n = word.size();
        int upper = 0;
        for (int i = 0; i < n; i++) {
            if (word[i] >= 'a' && word[i] <= 'z') {
                continue;
            } else {
                upper++;
            }
        }
        if (upper == n || upper == 0) return true;
        if (upper == 1 && (word[0] >= 'A' && word[0] <= 'Z')) return true;
        return false;
    }
};