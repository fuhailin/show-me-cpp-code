#include "bits/stdc++.h"

class Solution {
 public:
  vector<string> cellsInRange(string s) {
    vector<string> res;
    char c1 = s[0], c2 = s[3];
    char r1 = s[1], r2 = s[4];

    for (char i = c1; i <= c2; i++) {
      for (char j = r1; j <= r2; j++) {
        string path = "";
        path += i;
        path += j;
        res.emplace_back(path);
      }
    }
    return res;
  }
};

TEST(Sort, MergeSort) {
  Solution s;
  {
    std::string input = "K1:L2";
    std::vector<string> result = {"A1", "B1", "C1", "D1", "E1", "F1"};

    std::vector<string> ret = s.cellsInRange(input);

    EXPECT_EQ(ret, result);
  }
}