#include <vector>
#include <iostream>

using namespace std;

class Solution {
    vector<int> path;
    vector<vector<int>> res;
    void backtracking(vector<vector<int>>& graph, int idx) {
        if(idx == graph.size() - 1) {
            res.emplace_back(path);
            return;
        }
        for(auto & node : graph[idx]) {
            path.push_back(node);
            backtracking(graph, node);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        path.push_back(0);
        backtracking(graph, 0);
        return res;
    }
};