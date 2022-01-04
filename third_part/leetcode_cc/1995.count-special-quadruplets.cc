#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int countQuadruplets(vector<int>& nums) {
    int res = 0, a, b, c, d, n = nums.size();
    unordered_map<int, int> dict;
    for (b = n - 3; b >= 1; b--) {
      c = b + 1;
      for (d = c + 1; d < n; d++) {
        dict[nums[d] - nums[c]]++;
      }
      for (a = b - 1; a >= 0; a--) {
        res += dict[nums[a] + nums[b]];
      }
    }
    return res;
  }
};