#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        vector<string> res(n);
        map<int, int, std::greater<int>> rank;
        for (int i = 0; i < score.size(); i++) {
            rank.insert({score[i], i});
        }

        int i = 0;
        for (auto& it : rank) {
            if (i == 0) {
                res[it.second] = "Gold Medal";
            } else if (i == 1) {
                res[it.second] = "Silver Medal";
            } else if (i == 2) {
                res[it.second] = "Bronze Medal";
            } else {
                res[it.second] = to_string(i + 1);
            }
            i++;
        }
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> score = {1, 2, 3, 4, 5};
    vector<string> ret = so.findRelativeRanks(score);
    for (auto i : ret) {
        cout << i << endl;
    }
    return 0;
}
