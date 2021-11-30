#include <iostream>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n);

        function<bool(int)> safe = [&](int x) {
            if (color[x] > 0) {
                return color[x] == 2;
            }
            color[x] = 1;
            for (int y : graph[x]) {
                if (!safe(y)) {
                    return false;
                }
            }
            color[x] = 2;
            return true;
        };

        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (safe(i)) {
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    Solution s;
    vector<vector<int>> test = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    vector<int> res = s.eventualSafeNodes(test);
    for (auto x : res) {
        cout << "x"
             << " ";
    }
    return 0;
}
