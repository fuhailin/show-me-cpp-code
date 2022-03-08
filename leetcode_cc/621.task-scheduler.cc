#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int leastInterval(vector<char>& tasks, int n) {
      int len = tasks.size();
    vector<int> types(26);
    int _max = 0;
    for (char c : tasks) {
      _max = max(_max, ++types[c - 'A']);
    }
    int res = (_max - 1) * (n + 1);
    for (int i = 0; i < 25; i++) {
      if (types[i] == _max) {
        res++;
      }
    }

    //如果不同的任务种类数量大于n +
    // 1则可能不存在冷却时间，所以最后要比较一下结果和任务长度
    return max(res, len);
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<char> test = {'A', 'A', 'A', 'B', 'B', 'B'};
  int res = so.leastInterval(test, 2);
  cout << res << endl;
  return 0;
}