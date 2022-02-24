#include "bits/stdc++.h"

class Solution {
  vector<int> res;
  vector<int> path;
  int convert(vector<int> nums) {
    int res = 0;

    return res;
  }

  void backtracking(vector<int> &nums, vector<bool> &visited) {
    if (path.size() == nums.size()) {

      res.push_back(path);
      return;
    }
    for (int i = 0; i < nums.size(); ++i) {
      if (visited[i] || i > 0 && nums[i] == nums[i - 1] && !visited[i - 1])
        continue;
      visited[i] = true;
      path.push_back(nums[i]);
      backtracking(nums, visited);
      visited[i] = false;
      path.pop_back();
    }
  }

public:
  vector<int> findEvenNumbers(vector<int> &digits) {
    int n = digits.size();
    vector<bool> visited(n, false);
    sort(digits.begin(), digits.end());
    backtracking(digits, visited);
    return res;
  }
};

int main(int argc, const char **argv) {
  vector<int> test = {2, 1, 3, 0};
  Solution so;
  vector<int> res = so.findEvenNumbers(test);

  return 0;
}