#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {

    static bool comp(const vector<int>& a, const vector<int>& b)
    {
        return a[1] < b[1];
    }

public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals)
    {
        if (intervals.size() <= 1) {
            return 0;
        }
        sort(intervals.begin(), intervals.end(), comp);

        int arrow = 0;
        int pos = INT_MIN;
        for(int i = 0; i < intervals.size(); i++) {
            if(intervals[i][0] >= pos) {
                arrow++;
                pos = intervals[i][1];
            }
        }
        return intervals.size() - arrow;
    }
};