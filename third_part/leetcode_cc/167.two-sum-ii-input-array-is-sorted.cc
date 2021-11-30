#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int> &numbers, int target) {
    unordered_map<int, int> hashmap;
    for (int i = 0; i < numbers.size(); i++) {
      if (hashmap.find(numbers[i]) == hashmap.end()) {
        hashmap[target - numbers[i]] = i;
      } else {
        return {hashmap[numbers[i]] + 1, i + 1};
      }
    }
    return {-1, -1};
  }
};