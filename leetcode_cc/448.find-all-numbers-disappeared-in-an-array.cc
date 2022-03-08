#include <iostream>
#include <unordered_map>
#include <vector>

#include "glog/logging.h"
#include "glog/stl_logging.h"
using namespace std;

class Solution {
 public:
  vector<int> findDisappearedNumbers(vector<int>& nums) {
    vector<int> res;
    int n = nums.size();
    for (int num : nums) {
      int t = (num - 1) % n;
      nums[t] += n;
    }

    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] <= n) {
        res.push_back(i + 1);
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution* so = new Solution;
  vector<int> test = {4, 3, 2, 7, 8, 2, 3, 1};
  vector<int> res = so->findDisappearedNumbers(test);
  LOG(INFO) << res;
  return 0;
}