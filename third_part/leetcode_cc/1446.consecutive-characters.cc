#include "bits/stdc++.h"

class Solution {
public:
  int maxPower(string s) {
    int n = s.size();
    int res = 0;
    int left = 0;
    for (int right = 0; right < n; right++) {
      if (s[right] == s[left]) {
        res = max(res, right - left + 1);
      } else {
        while (s[left] != s[right]) {
          left++;
        }
      }
    }
    return res;
  }
};

int main(int argc, const char **argv) {
  Solution so;
  int res = so.maxPower("abbcccddddeeeeedcba");
  cout << res << endl;
  return 0;
}