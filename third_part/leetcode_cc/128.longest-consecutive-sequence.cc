#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    // unordered_set<int> hash(nums.begin(), nums.end());  //放入hash表中
    // int res = 0;
    // for (auto x : hash) {
    //   if (!hash.count(x - 1)) {
    //     int y = x;  //以当前数x向后枚举
    //     while (hash.count(y + 1)) y++;
    //     res = max(res, y - x + 1);  //更新答案
    //   }
    // }
    // return res;
    if (nums.empty()) return 0;
    unordered_set<int> hash(nums.begin(), nums.end());
    int res = 1, x;
    for (auto& num : hash) {
      if (hash.find(num + 1) == hash.end()) {
        x = num - 1;
        while (hash.find(x) != hash.end()) {
          x--;
        }
        res = max(res, num - x);
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
  int res = so.longestConsecutive(test);
  cout << res << endl;
  return 0;
}