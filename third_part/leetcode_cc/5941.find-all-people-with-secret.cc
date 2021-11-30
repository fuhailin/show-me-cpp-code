#include "bits/stdc++.h"

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        std::unordered_set<int> knows{0};
        map<int, unordered_set<int>> meets;
        for (vector<int> met : meetings) {
            if (meets.count(met[2])) {
                for (int i = 0; i < met.size() - 1; i++) {
                    meets[met[2]].insert(met[i]);
                }
            } else {
                std::unordered_set<int> fooSet(met.begin(), met.end() - 1);
                meets[met[2]] = fooSet;
            }
        }

        for (auto it : meets) {
            int time = it.first;
            unordered_set<int> persons = it.second;
            if (persons.count(firstPerson)) {
                knows.insert(persons.begin(), persons.end());
            }

            for (int per : persons) {
                if (knows.count(per)) {
                    knows.insert(persons.begin(), persons.end());
                }
            }
        }
        vector<int> res(knows.begin(), knows.end());
        return res;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;

    vector<vector<int>> meetings = {{0, 2, 1}, {1, 3, 1}, {4, 5, 1}};
    vector<int> res = so.findAllPeople(6, meetings, 1);
//    LOG(INFO) << res;
    return 0;
}