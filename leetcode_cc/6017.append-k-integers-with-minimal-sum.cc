
#include <unordered_set>

#include "bits/stdc++.h"

class Solution {
 public:
  long long minimalKSum(vector<int>& nums, int k) {
    long long res = 0;
    unordered_set<int> _set(nums.begin(), nums.end());
    int i = 1;
    while (k > 0) {
      if (_set.find(i) == _set.end()) {
        res += i;
        k--;
      }
      i++;
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {1, 4, 25, 10, 25};
  long long res = so.minimalKSum(test, 2);
  cout << res << endl;
  return 0;
}