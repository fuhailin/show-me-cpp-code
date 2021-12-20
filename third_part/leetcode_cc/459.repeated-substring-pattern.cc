#include "bits/stdc++.h"

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        return (s + s).find(s, 1) != s.size();
    }
};

int main(int argc, char const *argv[])
{
    Solution so;
    bool res = so.repeatedSubstringPattern("abab");
    cout << boolalpha << res << endl;
    return 0;
}
