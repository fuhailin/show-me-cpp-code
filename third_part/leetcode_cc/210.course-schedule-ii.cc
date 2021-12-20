#include <vector>
#include <queue>
using namespace std;


class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<int> res;
        vector<vector<int>> graph; // 邻接表存储有向图
        vector<int> indegree(numCourses); // 计算各节点的入度
        graph.resize(numCourses);
        for (auto& edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }

        queue<int> que;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            int root = que.front();
            res.push_back(root);
            que.pop();
            for (int node : graph[root]) {
                indegree[node]--;
                if (indegree[node] == 0) {
                    que.push(node);
                }
            }
        }
        if (res.size() != numCourses)
            return {};
        return res;
    }
};