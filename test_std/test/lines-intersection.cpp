/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/lines-intersection/
#  Email:            hailinfufu@outlook.com
#  Description:      求折线段与直线的交点数/
=============================================================================*/

#include <iostream>
#include <vector>
using namespace std;

int getSection(vector<int> vec, int val) {
  int sum = 0;
  if (vec.empty()) return 0;
  if (vec.size() == 1) {
    if ((vec[0] - val) == 0)
      return 1;
    else
      return 0;
  }
  for (int i = 1; i < vec.size(); i++) {
    if ((vec[i] - val) * (vec[i - 1] - val) <= 0) {
      sum++;
      if ((vec[i] - val) == 0) sum--;
      if ((vec[i] - val) == 0 && (vec[i - 1] - val) == 0) return -1;
    }
  }
  return sum;
}

int main(int argc, char const* argv[]) {
  vector<int> test{5, 3, 2, 1, 3};
  int res = getSection(test, 2);
  cout << res << endl;
  return 0;
}