#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int reversePairs(vector<int>& nums) {
    int res = 0;
    unordered_map<int, int> dict;
    for (int i = nums.size() - 1; i >= 0; i--) {
      int j = i + 1;
      while (j < nums.size() && nums[i] <= nums[j]) {
        j++;
      }
      if (j < nums.size()) {
        dict[i] = dict[j] + 1;
      } else {
        dict[i] = 0;
      }
      res += dict[i];
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {7, 5, 6, 4};
  int res = so.reversePairs(test);
  cout << res << endl;
  return 0;
}