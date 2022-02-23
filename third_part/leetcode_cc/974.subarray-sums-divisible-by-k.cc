#include <glog/logging.h>
#include <glog/stl_logging.h>

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> hashmap{{0, 1}};
    int res = 0, preSum = 0;
    for (auto& num : nums) {
      preSum += num;
      int left = (preSum % k + k) % k;
      LOG(INFO) << "left: " << left;
      if (hashmap.find(left) != hashmap.end()) {
        res += hashmap[left];
      }
      hashmap[left]++;
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {4, 5, 0, -2, -3, 1};
  int res = so.subarraysDivByK(test, 5);
  cout << res << endl;
  return 0;
}