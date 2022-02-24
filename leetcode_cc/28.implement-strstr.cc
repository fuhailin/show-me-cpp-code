#include "bits/stdc++.h"

struct KMP {
    vector<int> next;  // 失配时，模式串跳转位置

    void build(const string &pattern) {
        int n = pattern.length();
        next.resize(n + 1);
        for (int i = 0, j = next[0] = -1; i < n; next[++i] = ++j) {  // next(i) := 前s[0...i-1]的失配函数值
            while (~j && pattern[i] != pattern[j]) j = next[j];
        }
    }

    vector<int> find(const string &pattern, const string text) {
        build(pattern);
        vector<int> res;
        int n = pattern.length(), m = text.length();
        for (int i = 0, j = 0; i < m; ++i) {
            while (j > 0 && pattern[j] != text[i]) j = next[j];  // j > 0 是因为，当 j = 0时，我们直接在下面单独处理即可
            if (pattern[j] == text[i]) ++j;
            if (j == n) res.push_back(i - n + 1), j = next[j];
        }
        return res;
    }
};

class Solution {
   public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        KMP kmp;
        auto res = kmp.find(needle, haystack);
        return res.empty() ? -1 : res.front();
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.strStr("aabaabaafa", "aabaaf");
    cout << "res: " << res << endl;
    return 0;
}
