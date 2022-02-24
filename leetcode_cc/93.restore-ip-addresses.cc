// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;
#include "bits/stdc++.h"

class Solution {
    public:
    string path;
    vector<string> res;
    // 判断字符串s在左闭又闭区间[start, end]所组成的数字是否合法
    bool isValid(const string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        if (s[start] == '0' && start != end) { // 0开头的数字不合法
                return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }

    void backtracking(string s, int idx, int count) {
        if(count == 3) {
            if(isValid(s, idx, s.size() - 1)){
                path += s.substr(idx, s.size() - idx);
                res.emplace_back(path);
                path = path.substr(0, path.size() - (s.size() - idx));
            }
            return;
        }

        for(int i = idx; i < s.size(); i++) {
            if(isValid(s, idx, i)){
                path += s.substr(idx, i - idx + 1) + '.';
                backtracking(s, i + 1, count+1);
                path = path.substr(0, path.size() - (i - idx + 1));
            } else {
                break;
            }
        }
    }

    vector<string> restoreIpAddresses(string s) {
        backtracking(s, 0, 0);
        return res;
    }
};


int main(int argc, const char** argv) {
    Solution so;
    string test = "25525511135";
    vector<string> res = so.restoreIpAddresses(test);
    LOG(INFO) << res;
    return 0;
}