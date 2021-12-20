#include <ios>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool lemonadeChange(vector<int>& bills)
    {
        int five = 0, ten = 0;
        for (int bill : bills) {
            if (bill == 5) {
                five++;
            } else if (bill == 10) {
                if (five) {
                    ten++;
                    five--;
                } else {
                    return false;
                }
            } else {
                if (ten && five) {
                    ten--;
                    five--;
                } else if (five >= 3) {
                    five -= 3;
                } else {
                    return false;
                }
            }
        }
        return true;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    vector<int> test = { 5, 5, 10, 10, 20 };
    bool res = so.lemonadeChange(test);
    cout << boolalpha << res << endl;
    return 0;
}