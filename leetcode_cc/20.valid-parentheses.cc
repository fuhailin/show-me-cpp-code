#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> stk;
        for (auto &x : s) {
            switch (x) {
                case ')':
                    if (!stk.empty() && stk.top() == '(') {
                        stk.pop();
                    } else {
                        return false;
                    }
                    break;
                case '}':
                    if (!stk.empty() && stk.top() == '{') {
                        stk.pop();
                    } else {
                        return false;
                    }
                    break;
                case ']':
                    if (!stk.empty() && stk.top() == '[') {
                        stk.pop();
                    } else {
                        return false;
                    }
                    break;
                default:
                    stk.push(x);
                    break;
            }
        }
        return stk.empty();
    }
};