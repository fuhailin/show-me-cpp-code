#include "bits/stdc++.h"

class Solution {
    unordered_map<char, int> window, need;
   public:
    bool checkInclusion(string s1, string s2) {
        for (const auto &x : s1) {
            need[x]++;
        }
        int left = 0, valid = 0;
        for (int right = 0; right < s2.size(); right++) {
            char c = s2[right];
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }

            //判断是否窗口需要收缩
            while ((right - left + 1) >= s1.size()) {
                char x = s2[left];
                if (valid == need.size()) {
                    return true;
                }
                if (need.count(x)) {
                    if (window[x] == need[x]) {
                        valid--;
                    }
                    window[x]--;
                }
                left++;
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    bool res = so.checkInclusion("abc", "bbbca");
    cout << "res: " << boolalpha << res << endl;
    return 0;
}
