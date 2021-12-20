#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    int largestSumAfterKNegations(vector<int>& nums, int k)
    {
        int res = 0;
        std::priority_queue<int, vector<int>, std::greater<int>> _que;
        for (int num : nums) {
            res += num;
            _que.emplace(num);
        }
        for (int i = 0; i < k; i++) {
            int x = _que.top();
            _que.pop();
            _que.emplace(-x);
            res -= 2 * x;
        }
        return res;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    vector<int> test = { 2, -3, -1, 5, -4 };
    int res = so.largestSumAfterKNegations(test, 2);
    return 0;
}