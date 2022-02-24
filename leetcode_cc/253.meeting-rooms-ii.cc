#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

class Solution {
 public:
  int minMeetingRooms(vector<vector<int>>& intervals) {
    // priority_queue<pair<int, int>, std::greater> que;
    priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<>> que;
    for (auto& meeting : intervals) {
      que.push({meeting[0], 1});
      que.push({meeting[1], -1});
    }
    int rooms = 0, res = 0;
    while (!que.empty()) {
      auto met = que.top();
      que.pop();
      if (met.second == 1) {
        rooms++;
      } else {
        rooms--;
      }
      res = max(res, rooms);
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<vector<int>> test = {{0, 30}, {5, 10}, {15, 20}};
  int res = so.minMeetingRooms(test);
  cout << res << endl;
  return 0;
}