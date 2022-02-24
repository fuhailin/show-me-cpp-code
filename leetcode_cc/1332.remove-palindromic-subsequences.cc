#include <string>
using namespace std;

class Solution {
  bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
      if (s[left] != s[right]) {
        return false;
      }
      left++;
      right--;
    }
    return true;
  }

 public:
  int removePalindromeSub(string s) { 
      return isPalindrome(s) ? 1 : 2; 
      }
};