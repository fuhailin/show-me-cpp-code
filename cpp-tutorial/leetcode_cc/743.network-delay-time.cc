#include <vector>
#include <queue>
using namespace std;

class Solution {
   public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        const int inf = INT_MAX / 2;  //两边距离相加防止溢出
        vector<vector<int>> graph(n, vector<int>(n, inf));
        for (vector<int>& edge : times) {
            graph[edge[0] - 1][edge[1] - 1] = edge[2];
        }

        vector<int> dist(n, inf);
        dist[k - 1] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<>> uesd;
        used.emplace(0, k -1);

        while(!used.empty()){
            auto visit = used.pop();
            int time = visit.first, index = visit.second;

            for
        }

        

        int ans = *max_element(dist.begin(), dist.end());
        return ans == inf ? -1 : ans;
    }
};