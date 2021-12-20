#include <iostream>
#include <vector>
using namespace std;

class Solution {

    static bool comp(const vector<int>& a, const vector<int>& b)
    {
        return a[0] < b[0];
    }

public:
    vector<vector<int>> merge(vector<vector<int>>& intervals)
    {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end(), comp);
        vector<int> range = { intervals[0][0], intervals[0][1] };
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] > range[1]) {
                res.emplace_back(range);
                range[0] = intervals[i][0];
                range[1] = max(range[1], intervals[i][1]);
            } else {
                range[1] = max(intervals[i][1], range[1]);
            }
        }
        res.emplace_back(range);
        return res;
    }
};