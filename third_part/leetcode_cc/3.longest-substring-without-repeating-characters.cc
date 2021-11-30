#include "bits/stdc++.h"

class Solution {
    unordered_map<char, int> window;

   public:
    int lengthOfLongestSubstring(string s) {
        int left = 0, res = INT_MIN;
        for (int right = 0; right < s.size(); right++) {
            char c = s[right];
            window[c]++;
            if (window[c] <= 1) {
                res = max(res, right - left + 1);
            } else {
                // 判断窗口是否需要收缩
                while (window[c] > 1) {
                    window[s[left]]--;
                    left++;
                }
            }
        }
        return res == INT_MIN ? 0 : res;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.lengthOfLongestSubstring(" ");
    cout << "res: " << res << endl;
    return 0;
}
