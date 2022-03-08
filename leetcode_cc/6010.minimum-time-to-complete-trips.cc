#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  bool check(long long mid, vector<int>& time, int x) {
    int n = time.size();
    long long cnt = 0;
    for (int i = 0; i < n; ++i) {
      cnt += mid / time[i];
      if (cnt >= x) return true;
    }
    return cnt >= x;
  }
  long long minimumTime(vector<int>& time, int total) {
    int n = time.size();
    long long l = 1;
    long long mn = *min_element(time.begin(), time.end());
    long long r = 1LL * total * mn;
    while (l < r) {
      long long mid = ((r - l) >> 1) + l;
      if (check(mid, time, total)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {10000};
  //   vector<int> test = {

  //   long long res = so.minimumTime(test, 9765277);
  long long res = so.minimumTime(test, 10000000);

  cout << res << endl;
  return 0;
}