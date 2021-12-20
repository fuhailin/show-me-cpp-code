#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {

public:
    long long getDescentPeriods(vector<int>& prices)
    {
        if (prices.size() < 2)
            return prices.size();
        vector<long long> dp(prices.size() + 1);
        dp[2] = 1;
        //        动态规划
        for (int i = 3; i <= prices.size(); i++) {
            dp[i] = dp[i - 1] + i - 1;
        }
        long long result = 0;
        result += prices.size();
        int left = 0, right;
        //        滑动窗口
        for (right = 1; right < prices.size(); right++) {
            if (prices[right] != prices[right - 1] - 1) {
                if (right - left > 1) {
                    result += dp[right - left];
                }
                left = right;
            }
        }
        if (right - left > 1) {
            result += dp[right - left];
        }
        return result;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    vector<int> test = { 100000, 100000 };
    long long res = so.getDescentPeriods(test);
    cout << res << endl;
    return 0;
}