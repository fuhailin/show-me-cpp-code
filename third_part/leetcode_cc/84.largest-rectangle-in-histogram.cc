#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int res = INT_MIN;
    stack<int> stk;
    int i = 0;
    while (i < heights.size()) {
      // 栈为空或者新元素大于栈顶元素即可入栈
      if (stk.empty() || heights[i] >= heights[stk.top()]) {
        stk.push(i);
        i++;
      } else {  // 出栈
        int k = stk.top();
        stk.pop();
        if(stk.empty()) {
            res = max(res, heights[k] * i);
        } else {
            res = max(res, heights[k] * (i - stk.top() - 1));
        }
      }
    }
    while (!stk.empty()) {
      int k = stk.top();
      stk.pop();
      if(stk.empty()) {
          res = max(res, heights[k] * (i - 0));
      } else {
          res = max(res, heights[k] * (i - stk.top() - 1));
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {4,2,0,3,2,5};
  int res = so.largestRectangleArea(test);
  cout << res << endl;
  return 0;
}