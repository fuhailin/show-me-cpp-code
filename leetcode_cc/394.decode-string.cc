#include <iostream>
#include <stack>
#include <string>
using namespace std;

class Solution {
 public:
  string decodeString(string s) {
    stack<pair<int, string>> stk;
    string res;
    int multi = 0;
    int i = 0;
    while (i < s.size()) {
      char c = s[i++];
      if (c >= '0' && c <= '9') {
        multi = multi * 10 + c - '0';
      } else if (c == '[') {
        stk.push({multi, res});
        multi = 0;
        res = "";
      } else if (c == ']') {
        int n = stk.top().first;
        string txt = stk.top().second;
        stk.pop();
        for (int j = 0; j < n; j++) {
          txt += res;
        }
        res = txt;
      } else {
        res += c;
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  string test = "3[a]2[bc]";
  string res = so.decodeString(test);
  cout << res << endl;
  return 0;
}