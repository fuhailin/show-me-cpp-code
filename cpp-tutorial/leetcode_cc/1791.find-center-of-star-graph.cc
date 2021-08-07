#include <vector>
using namespace std;

class Solution {
   public:
    int findCenter(vector<vector<int>> &edges) {
        int n = edges.size() + 1;
        vector<int> mMap(n, 0);
        for (auto edge : edges) {
            for (auto it : edge) {
                if ((++mMap[it]) > 1) {
                    return it;
                }
            }
        }
        return -1;
    }
};