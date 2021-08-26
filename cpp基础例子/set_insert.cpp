#include <stdio.h>
#include <vector>
using namespace std;

class Solution {
    bool dfs(vector<vector<int>>& graph, vector<bool>& visited, int i) {
        if (visited[i]) return false;
        visited[i] = true;
        for (auto neibor : graph[i]) {
            if (!dfs(graph, visited, neibor)) return false;
        }
        visited[i] = false;
        graph[i].clear();
        return true;
    }

public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<bool> visited(n, false);

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (dfs(graph, visited, i))
                ans.push_back(i);
        }
        return ans;
    }
};

int main()
{
    Solution s;
    // printf("Hello World");
    vector<vector<int>> test = {{1,2},{2,3},{5},{0},{5},{},{}};
    auto res = s.eventualSafeNodes(test);

    return 0;
}
