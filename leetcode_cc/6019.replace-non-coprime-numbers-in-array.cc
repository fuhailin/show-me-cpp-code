#include "bits/stdc++.h"

class Solution {
  // Recursive function to return gcd of a and b
  long long gcd(long long int a, long long int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
  }

  // Function to return LCM of two numbers
  long long lcm(int a, int b) { return (a / gcd(a, b)) * b; }

 public:
  vector<int> replaceNonCoprimes(vector<int>& nums) {
    if (nums.size() < 2) return nums;
    vector<int> res;
    for (int i = 0; i < nums.size(); i++) {
      res.emplace_back(nums[i]);
      while (res.size() > 1) {
        int a = res[res.size() - 1];
        int b = res[res.size() - 2];
        int _gcd = gcd(a, b);
        if (_gcd > 1) {
          res.pop_back();
          res.pop_back();
          int _lcm = lcm(a, b);
          res.emplace_back(_lcm);
        } else {
          break;
        }
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {287, 41, 49, 287, 899, 23, 23, 20677, 5, 825};
  vector<int> res = so.replaceNonCoprimes(test);
  LOG(INFO) << res;
  return 0;
}