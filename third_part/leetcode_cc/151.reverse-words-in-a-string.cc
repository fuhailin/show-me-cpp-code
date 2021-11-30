#include "bits/stdc++.h"

class Solution {
    void removeExtraSpaces(string &s) {
        int slow = 0, fast = 0;
        // remove front space
        while (s[fast] == ' ' && fast < s.size()) {
            fast++;  //很奇怪这里是if，会被前面有单个卡住， 不知道why。
        }
        while (fast < s.size()) {
            if (fast - 1 > 0 && s[fast - 1] == s[fast] && s[fast] == ' ') {
                fast++;
            } else {
                s[slow++] = s[fast++];
            }
        }  //remove medium space
        if (slow - 1 > 0 && s[slow - 1] == ' ') {
            s.resize(slow - 1);  //remove final space
        } else {
            s.resize(slow);
        }
    }

public:
    string reverseWords(string s) {
        removeExtraSpaces(s);
        reverse(s.begin() + left, s.end());
        int left = 0;
        for (int right = 0; right < s.size(); right++) {
            if (right == s.size() - 1) {
                std::reverse(s.begin() + left, s.end());
            } else if (s[right] == ' ') {
                std::reverse(s.begin() + left, s.begin() + right);
                left = right + 1;
            }
        }
        return s;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    string test = "  Bob    Loves  Alice   ";
    string res = so.reverseWords(test);
    cout << res << endl;
    return 0;
}
