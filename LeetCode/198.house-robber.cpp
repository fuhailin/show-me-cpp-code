#include <iostream>
#include <vector>
using namespace std;
class Solution
{
  public:
    int rob(vector<int> &nums)
    {
        if (nums.size() == 0)
            return 0;
        int prev1 = 0;
        int prev2 = 0;
        for (auto num : nums)
        {
            int tmp = prev1;
            prev1 = max(prev2 + num, prev1);
            prev2 = tmp;
        }
        return prev1;
    }
};
int main(int argc, char const *argv[])
{
    vector<int> test{1, 2, 3, 1};
    int res = Solution().rob(test);
    cout << boolalpha << res << endl;
    return 0;
}