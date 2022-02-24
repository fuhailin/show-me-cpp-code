#include "bits/stdc++.h"

class Solution {
    string path;
    vector<string> res;
    pair<int, int> count_remove(string &s) {
        int lremove = 0, rremove = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                lremove++;
            } else if (s[i] == ')') {
                if (lremove > 0) {
                    lremove--;
                } else {
                    rremove++;
                }
            }
        }
        return {lremove, rremove};
    }

    void backtracking(string &s, int lremove, int rremove, int idx, string &t, int lcnt, int rcnt, int flag) {
        if (idx == s.size()) {
            if (lremove == 0 && rremove == 0) {
                res.emplace_back(t);
            }
            return;
        }

        char x = s[idx];
        if (x == '(') {
            // save this '('
            // flag 为 false 说明前面的左括号没要，那这个左括号也不能要
            if((flag && 1) == 0) {
                t.push_back(x);
                backtracking(s, lremove, rremove, idx + 1, t, lcnt + 1, rcnt, 0);
                t.pop_back();
            }
            // drop this '('
            if (lremove > 0) {
                // 不要当前这个左括号，后面的左括号也不能要
                backtracking(s, lremove - 1, rremove, idx + 1, t, lcnt, rcnt, flag || 1);
            }

        } else if (x == ')') {
            if (lcnt > rcnt) {
                // save this ')'
                if((flag && 2) == 0) {
                    t.push_back(x);
                    backtracking(s, lremove, rremove, idx + 1, t, lcnt, rcnt + 1, true);
                    t.pop_back();
                }
            }
            // drop this ')'
            if (rremove > 0) {
                backtracking(s, lremove, rremove - 1, idx + 1, t, lcnt, rcnt, flag || 2);
            }
        } else {
            t.push_back(x);
            backtracking(s, lremove, rremove, idx + 1, t, lcnt, rcnt, 0);
            t.pop_back();
        }
    }

public:
    vector<string> removeInvalidParentheses(string s) {
        pair<int, int> remove = count_remove(s);
        if (remove.first == 0 && remove.second == 0) {
            return {s};
        }
        backtracking(s, remove.first, remove.second, 0, path, 0, 0, 0);
        return res;
    }
};

int main(int argc, char const *argv[]) {
    int a = 0;
    int b = 2;
    int c = a || b;
    Solution so;
    string test = "()())()";
    vector<string> res = so.removeInvalidParentheses(test);
    LOG(INFO) << "res: " << res;
    return 0;
}
