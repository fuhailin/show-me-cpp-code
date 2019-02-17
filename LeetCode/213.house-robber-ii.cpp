#include <iostream>
#include <vector>

using namespace std;
class Solution
{
  public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
            return n ? nums[0] : 0;
        return max(rob(nums, 0, nums.size() - 1), rob(nums, 1, nums.size()));
    }

  private:
    int rob(vector<int> &nums, int left, int right)
    {
        int prev1 = 0, prev2 = 0;
        for (int i = left; i < right; i++)
        {
            int tmp = prev1;
            prev1 = max(prev2 + nums[i], prev1);
            prev2 = tmp;
        }
        return prev1;
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}