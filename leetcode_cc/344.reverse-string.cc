#include "bits/stdc++.h"

class Solution {
 public:
  void reverseString(vector<char>& s) {
    int n = s.size();
    int left = 0, right = n - 1;
    while (left < right) {
      swap(s[left++], s[right--]);
    }
  }
};

int main(int argc, char const* argv[]) {
  vector<char> test{'h', 'e', 'l', 'l', 'o'};
  reverseString(test);
  for (int i = 0; i < test.size(); i++) {
    cout << test[i];
  }
  return 0;
}