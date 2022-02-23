
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
  typedef pair<int, int> PII;

 public:
  int minimumOperations(vector<int>& nums) {
    int res;
    unordered_map<int, int> even, odd;
    for (int i = 0; i < nums.size(); i++) {
      if (i & 1) { /* 将奇偶数组存入map中 */
        even[nums[i]]++;
      } else {
        odd[nums[i]]++;
      }
    }

    /* 将数值和出现次数, 存入vector中, 按从大到小排序 */
    vector<PII> v0(1), v1(1);
    for (auto& [num, cnt] : even) {
      v0.emplace_back(cnt, num);
    }

    for (auto& [num, cnt] : odd) {
      v1.emplace_back(cnt, num);
    }

    sort(v0.begin(), v0.end(), greater<>());
    sort(v1.begin(), v1.end(), greater<>());

    /* 判断最大次数的数值是否相等, 如果不相等, 取两个最大值相加;
           否则取最大和次大相加 */
    if (v0[0].second != v1[0].second) {
      return nums.size() - v0[0].first - v1[0].first;
    }
    return nums.size() -
           max(v0[0].first + v1[1].first, v0[1].first + v1[0].first);

    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {3, 1, 3, 2, 4, 3};
  int res = so.minimumOperations(test);
  cout << res << endl;
  return 0;
}