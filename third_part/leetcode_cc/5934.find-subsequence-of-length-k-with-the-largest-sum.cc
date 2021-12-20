#include <climits>
#include <numeric>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
    
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> que;
        for(int i = 0; i < nums.size(); i++) {
            que.push({nums[i], i});
        }
        vector<int> tmp(nums.size(), INT_MIN);
        for(int i = 1; i <= k; i++) {
            auto it = que.top();
            tmp[it.second] = it.first;
            que.pop();
        }
        vector<int> res;
        for(auto &value : tmp) {
            if(value != INT_MIN) {
                res.push_back(value);
            }
        }
        return res;
    }
};