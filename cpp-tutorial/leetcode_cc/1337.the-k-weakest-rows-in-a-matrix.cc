#include <algorithm>
#include <map>
#include <vector>

using namespace std;
class Solution {
    typedef pair<int, int> p;

   public:
    vector<int> kWeakestRows(vector<vector<int> >& mat, int k) {
        vector<p> v;
        for (int i = 0; i < mat.size(); i++) {
            int ans = std::accumulate(mat[i].begin(), mat[i].end(), 0);
            p temp = make_pair(i, ans);
            v.emplace_back(temp);
        }
        auto cmp = [](p a, p b) {
            if(a.second==b.second) return a.first<b.first; 
            return a.second<b.second; };
        sort(v.begin(), v.end(), cmp);
        vector<int> ret;
        for (int i = 0; i < k; i++) {
            ret.emplace_back(v[i].first);
        }
        return ret;
    }
};