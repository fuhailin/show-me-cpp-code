#include "bits/stdc++.h"

class Solution {
    void reverseString(string& s, int left, int right) {
        while (left < right) {
            swap(s[left++], s[right--]);
        }
    }

public:
    string reverseStr(string s, int k) {
        int n = s.size();
        int left = 0, right = 0;
        do {
            right += 2 * k;
            if (right - left > k) {
                reverseString(s, left, min(left + k - 1, n - 1));
            } else {
                reverseString(s, left, n - 1);
            }
            left = right;
        } while (right < n);
        return s;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    string res = so.reverseStr("a", 2);
    cout << res << endl;
    return 0;
}
