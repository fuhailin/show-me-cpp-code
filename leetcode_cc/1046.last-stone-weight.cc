#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    int lastStoneWeight(vector<int>& stones) {
        priority_queue<int> pq;
        for (auto s : stones) pq.push(s);
        while (pq.size() > 1) {
            int a = pq.top();
            pq.pop();
            int b = pq.top();
            pq.pop();
            if (a != b) pq.push(a - b);
        }
        return pq.empty() ? 0 : pq.top();
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> stones = {2, 2};
    cout << so.lastStoneWeight(stones) << endl;
    return 0;
}
