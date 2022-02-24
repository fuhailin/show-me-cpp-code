#include <glog/logging.h>
#include <glog/stl_logging.h>

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int numberOfSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> odd(n + 1);

    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] % 2 == 1) {
        odd[i + 1] = odd[i] + 1;
      } else {
        odd[i + 1] = odd[i];
      }
    }
    LOG(INFO) << "odd: " << odd;
    int res = 0;

    unordered_map<int, int> hashmap;
    hashmap[0] = 1;

    for (int i = 1; i < odd.size(); i++) {
      if (hashmap.find(odd[i] - k) != hashmap.end()) {
        res += hashmap[odd[i] - k];
      }
      hashmap[odd[i]]++;
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {1, 1, 2, 1, 1};
  int res = so.numberOfSubarrays(test, 3);
  cout << res << endl;
  return 0;
}