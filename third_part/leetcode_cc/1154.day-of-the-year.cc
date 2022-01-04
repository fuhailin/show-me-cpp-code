#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int dayOfYear(string date)
    {
        vector<int> months = { 31,
            28,
            31,
            30,
            31,
            30,
            31,
            31,
            30,
            31,
            30,
            31 };
        string yy = date.substr(0, 4);
        string mm = date.substr(5, 2);
        string dd = date.substr(8, 2);

        int y = stoi(yy);
        int m = stoi(mm);
        int d = stoi(dd);

        int res = 0;
        if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
            months[1]++;
        for (int i = 0; i < m - 1; i++) {
            res += months[i];
        }
        res += d;
        return res;
    }
};