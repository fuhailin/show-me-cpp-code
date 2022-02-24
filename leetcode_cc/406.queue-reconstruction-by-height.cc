#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Solution {
    static bool cmp(const vector<int> a, const vector<int> b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] > b[0];
    }

public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people)
    {
        sort(people.begin(), people.end(), cmp);
        list<vector<int>> res;
        for (int i = 0; i < people.size(); i++) {
            int pos = people[i][1];
            std::list<vector<int>>::iterator it = res.begin();
            while (pos--) {
                it++;
            }
            res.insert(it, people[i]);
        }
        vector<vector<int>> result(res.begin(), res.end());
        return result;
    }
};

int main(int argc, const char** argv)
{
    vector<vector<int>> test = {
        { 7, 0 },
        { 4, 4 },
        { 7, 1 },
        { 5, 0 },
        { 6, 1 },
        { 5, 2 }
    };
    vector<vector<int>> res = Solution::reconstructQueue(test);
    return 0;
}