#include <string>
#include <vector>
using namespace std;

class Solution {
  int getTime(string timePoint) {
    return ((timePoint[0] - '0') * 10 + timePoint[1] - '0') * 60 +
           (timePoint[3] - '0') * 10 + timePoint[4] - '0';
  }

 public:
  int findMinDifference(vector<string>& timePoints) {
    if (timePoints.size() > 1440) return 0;
    sort(timePoints.begin(), timePoints.end());
    int res = INT_MAX;
    int t0 = getTime(timePoints[0]);
    int preTime = t0, time;
    for (int i = 1; i < timePoints.size(); ++i) {
      time = getTime(timePoints[i]);
      res = min(res, time - preTime);  // 相邻时间的时间差
      preTime = time;
    }
    res = min(res, t0 + 1440 - preTime);  // 首尾时间的时间差
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<string> test = {"23:59", "00:00"};
  int res = so.findMinDifference(test);
  return 0;
}