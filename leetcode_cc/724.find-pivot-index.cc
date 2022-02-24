#include <glog/logging.h>
#include <glog/stl_logging.h>

#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int pivotIndex(vector<int>& nums) {
    vector<int> left(nums.size()), right(nums.size());
    left[0] = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      left[i] = nums[i] + left[i - 1];
    }

    right[nums.size() - 1] = nums[nums.size() - 1];
    for (int i = nums.size() - 2; i >= 0; i--) {
      right[i] = nums[i] + right[i + 1];
    }

    LOG(INFO) << "left: " << left;
    LOG(INFO) << "right: " << right;
    for (int i = 0; i < nums.size(); i++) {
      if (left[i] == right[i]) {
        return i;
      }
    }
    return -1;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  //   vector<int> test = {1, 7, 3, 6, 5, 6};
  vector<int> test = {-1, -1, 0, 1, 1, 0};
  int res = so.pivotIndex(test);
  cout << res << endl;
  return 0;
}