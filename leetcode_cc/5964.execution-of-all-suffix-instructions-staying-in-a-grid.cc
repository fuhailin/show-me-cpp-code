#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> executeInstructions(int n, vector<int>& startPos, string s) {
    vector<int> res;
    for (int i = 0; i < s.size(); i++) {
      int preRes = 0;
      int x = startPos[0], y = startPos[1];
      int j = i;
      while (j < s.size()) {
        char command = s[j];
        if (command == 'U') {
          x -= 1;
        } else if (command == 'D') {
          x += 1;
        } else if (command == 'L') {
          y -= 1;
        } else if (command == 'R') {
          y += 1;
        }
        if (x >= n || x < 0 || y >= n || y < 0 || j == s.size() - 1) {
          if (j == s.size() - 1 && x >= 0 && x < n && y >= 0 && y < n) {
            res.push_back(preRes + 1);
          } else {
            res.push_back(preRes);
          }
          break;
        } else {
          preRes++;
        }
        j++;
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {0, 1};
  vector<int> res = so.executeInstructions(3, test, "RRDDLU");
  return 0;
}