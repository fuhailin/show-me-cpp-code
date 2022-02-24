// #include <glog/logging.h>
// #include <glog/stl_logging.h>

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int subarraySum(vector<int>& nums, int k) {
    int n = nums.size();

    unordered_map<int, int> sum_count; // 前缀和为sum 出现的次数为count
    sum_count[0] = 1;
    int res = 0, preSum = 0;
    for (int i = 0; i < n; i++) {
      preSum += nums[i];
      if (sum_count.find(preSum - k) != sum_count.end()) {
        res += sum_count[preSum - k];
      }
      sum_count[preSum]++;
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {1, 2, 3};
  int res = so.subarraySum(test, 3);
  cout << res << endl;
  return 0;
}