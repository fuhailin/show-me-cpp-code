#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int findRadius(vector<int>& houses, vector<int>& heaters)
    {
        int res = INT_MIN;
        sort(heaters.begin(), heaters.end());
        for (int house : houses) {
            // 找到house在heaters中的插入位置
            int up_pos = upper_bound(heaters.begin(), heaters.end(), house) - heaters.begin();
            int right = up_pos >= heaters.size() ? INT_MAX : heaters[up_pos] - house;
            int left = up_pos - 1 < 0 ? INT_MAX : house - heaters[up_pos - 1];
            res = max(res, min(right, left));
        }
        return res;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    vector<int> test = { 1, 2, 3, 4 };
    vector<int> test1 = { 1, 4 };
    int res = so.findRadius(test, test1);
    cout << res << endl;
    return 0;
}