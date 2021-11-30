#include <iostream>
#include <string>
using namespace std;

class Solution {
   public:
    int lengthOfLastWord(string s) {
        int ans = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            if (s[i] == ' ') continue;
            while (s[i] != ' ' && i >= 0) {
                ans++;
                i--;
            }
            return ans;
        }
    }
};