
#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
 public:
  int longestValidParentheses(string s) {
    stack<int> stk;
    stk.emplace(-1);
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == '(') {
        stk.emplace(i);
      } else {
        stk.pop();
        if (stk.empty()) {
          stk.emplace(i);
        } else {
          ans = max(ans, i - stk.top());
        }
      }
    }
    return ans;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  string test = ")()())";
  int res = so.longestValidParentheses(test);
  cout << res << endl;
  return 0;
}