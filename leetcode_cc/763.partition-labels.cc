#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s)
    {
        if (s.size() <= 1) {
            return { int(s.size()) };
        }
        vector<int> res;
        unordered_map<char, int> dict;
        for (int i = 0; i < s.size(); i++) {
            dict[s[i]] = i;
        }

        vector<int> range = { 0, 0 };
        for (int i = 0; i < s.size(); i++) {
            range[1] = max(range[1], dict[s[i]]);
            if (i == range[1]) {
                res.push_back(range[1] - range[0] + 1);
                range[0] = range[1] + 1;
            }
        }
        return res;
    }
};