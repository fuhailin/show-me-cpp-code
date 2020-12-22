#include <iostream>
#include <vector>
#define MAX_Integer 0x7fffffff
using namespace std;
class Solution
{
  public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount == 0 || coins.size() == 0)
            return 0;
        vector<int> dp(amount + 1, MAX_Integer);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (auto coin : coins)
            {
                if ((i - coin) == 0)
                    dp[i] = 1;
                else if ((i - coin) > 0)
                {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};
int main(int argc, char const *argv[])
{
    vector<int> test{1, 2, 5};
    int res = Solution().coinChange(test, 11);
    cout << res << endl;
    return 0;
}