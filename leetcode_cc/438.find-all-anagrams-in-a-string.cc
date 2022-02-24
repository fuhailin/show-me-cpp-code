#include "bits/stdc++.h"

class Solution {
    unordered_map<char, int> window, need;

   public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        for (const auto &x : p) {
            need[x]++;
        }
        int left = 0, valid = 0;
        for (int right = 0; right < s.size(); right++) {
            char c = s[right];
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }

            //判断是否窗口需要收缩
            while ((right - left + 1) >= p.size()) {
                char x = s[left];
                if (valid == need.size()) {
                    res.push_back(left);
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
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    vector<int> res = so.findAnagrams("abab", "ab");
    LOG(INFO) << res;
    return 0;
}
