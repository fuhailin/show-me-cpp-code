#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    static bool cmp(const vector<int>& a, const vector<int>& b)
    {
        return a[1] < b[1];
    }

public:
    int findMinArrowShots(vector<vector<int>>& points)
    {
        if (points.size() <= 1)
            return points.size();
        sort(points.begin(), points.end(), cmp);

        int arrow = 1;
        int cur = points[0][1];
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > cur) {
                cur = points[i][1];
                arrow++;
            }
        }
        return arrow;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    vector<vector<int>> test = {
        { 10, 16 },
        { 2, 8 },
        { 1, 6 },
        { 7, 12 }
    };
    int res = so.findMinArrowShots(test);
    cout << res << endl;
    return 0;
}