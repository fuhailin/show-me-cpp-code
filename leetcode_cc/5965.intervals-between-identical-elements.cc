#include <math.h>

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<long long> getDistances(vector<int>& arr) {
    vector<long long> res(arr.size());
    unordered_map<int, long long> map_res;
    unordered_map<int, vector<int>> dict;
    for (int i = 0; i < arr.size(); i++) {
      dict[arr[i]].push_back(i);
    }

    for (auto& it : dict) {
      long long tmp = 0;
      int i = it.second[0];
      for (int j = 1; j < it.second.size(); j++) {
        tmp += abs(i - j);
      }
      map_res.insert({it.first, tmp * it.second.size()});
    }
    for (int i = 0; i < arr.size(); i++) {
      res[i] = map_res[arr[i]];
    }

    // for (int i = 0; i < arr.size(); i++) {
    //   long long tmp = 0;
    //   for (int j : dict[arr[i]]) {
    //     if (i != j) {
    //       tmp += abs(i - j);
    //     }
    //   }
    //   res.push_back(tmp);
    // }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<int> test = {2, 1, 3, 1, 2, 3, 3};
  vector<long long> res = so.getDistances(test);
  return 0;
}