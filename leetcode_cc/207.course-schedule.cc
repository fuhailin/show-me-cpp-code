#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    bool
    canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<int> res;
        vector<vector<int>> graph;  // 邻接表存储有向图
        vector<int> indegree(numCourses); // 计算各节点的入度
        graph.resize(numCourses);
        for (auto& edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }

        queue<int> que;
        for (int i = 0; i < numCourses; i++) {
            if(indegree[i] == 0) {
                que.push(i);
            }
        }
        while (!que.empty()) {
            int root = que.front();
            res.push_back(root);
            que.pop();
            for(int node : graph[root]) {
                indegree[node]--;
                if(indegree[node] == 0) {
                    que.push(node);
                }
            }
        }
        return res.size() == numCourses;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    vector<vector<int>> test = {
        { 1, 0 },
        { 0, 1 }
    };
    bool res = so.canFinish(2, test);
    return 0;
}