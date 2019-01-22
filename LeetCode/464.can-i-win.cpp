#include <iostream>
using namespace std;
class Solution
{
  public:
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        int sum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
        if (sum < desiredTotal)
            return false;
        if (desiredTotal <= maxChoosableInteger)
            return true;
    }
};

int main(int argc, char const *argv[])
{
    int maxChoosableInteger, desiredTotal;
    Solution solu;
    // bool res = solu.canIWin(maxChoosableInteger, desiredTotal);
    return 0;
}
