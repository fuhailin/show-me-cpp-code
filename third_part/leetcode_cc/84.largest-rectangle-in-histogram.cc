#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int largestRectangleArea(vector<int>& heights) {
    int res = INT_MIN;
    for (int i = 0; i < heights.size(); i++) {
      int left = i;
      while (left >= 0 && heights[left] >= heights[i]) {
        left--;
      }
      int right = i;
      while (right < heights.size() && heights[right] >= heights[i]) {
        right++;
      }
      res = max(res, (right - left - 1) * heights[i]);
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {2, 1, 5, 6, 2, 3};
  int res = so.largestRectangleArea(test);
  cout << res << endl;
  return 0;
}