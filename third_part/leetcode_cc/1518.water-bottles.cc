#include <iostream>
using namespace std;

class Solution {

public:
    int numWaterBottles(int numBottles, int numExchange)
    {
        int res = 0;
        int empty = 0;
        while (numBottles > 0) {
            res += numBottles;
            empty += numBottles;
            numBottles = empty / numExchange;
            empty = empty % numExchange;
        }
        return res;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    int res = so.numWaterBottles(15, 4);
    cout << res << endl;
    return 0;
}