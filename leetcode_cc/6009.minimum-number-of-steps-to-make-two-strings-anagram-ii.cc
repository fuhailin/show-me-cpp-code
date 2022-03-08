#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int minSteps(string s, string t) {
    unordered_map<char, int> dicts, dictt;
    for (char c : s) {
      dicts[c]++;
    }

    for (char c : t) {
      dictt[c]++;
    }

    string lefts = "", leftt = "";
    for (char c : s) {
      if (dictt[c] != 0) {
        dictt[c]--;
      } else {
        lefts += c;
      }
    }

    for (char c : t) {
      if (dicts[c] != 0) {
        dicts[c]--;
      } else {
        leftt += c;
      }
    }

    int res = lefts.size() + leftt.size();
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;

  //   int res = so.minSteps("leetcode", "coats");
  int res = so.minSteps("night", "thing");
  cout << res << endl;

  return 0;
}