#include <iostream>
#include <vector>
using namespace std;

int FindGreatestSumOfSubArray(vector<int> array)
{
    if (array.size() <= 0)
        return 0;
    int n = array.size();
    vector<int> dp(n);
    int max = dp[0];

    for (int i = 0; i < n; i++)
    {
        dp[i] = array[i] + (dp[i - 1] > 0 ? dp[i - 1] : 0);
        max = std::max(max, dp[i]);
    }
    return max;
}

int main()
{
    vector<int> testcase = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res = FindGreatestSumOfSubArray(testcase);
    cout << res << endl;

    return 0;
}