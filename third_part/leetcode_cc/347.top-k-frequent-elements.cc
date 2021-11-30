#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
    struct comp  //运算符重载<
    {
        bool operator()(pair<int, int> const& a, pair<int, int> const& b) const {
            return a.second < b.second;  //小顶堆
        }
    };

   public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> dict;
        for (int num : nums) {
            dict[num]++;
        }

        std::priority_queue<pair<int, int> > pri_que;
        for (auto& [num, count] : dict) {
            pri_que.emplace_back(num, count);
        }
        vector<int> res;

        while (k--) {
            auto it = pri_que.top();
            res.emplace_back(it.first);
            pri_que.pop();
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    return 0;
}
