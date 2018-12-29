#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
  public:
    int maxSubArray(vector<int> &nums)
    {
        return divide(nums, 0, nums.size() - 1);
    }

    int maxSubArray_DP(vector<int> &nums)
    {
        int maxsum = nums[0], maxhere = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (maxhere <= 0)
                maxhere = nums[i];
            else
                maxhere += nums[i];
            if (maxhere > maxsum)
                maxsum = maxhere;
        }
        return maxsum;
    }

    int maxSubArray(vector<int> &nums)
    {
        int res = nums[0];
        int sum = 0;
        for (int num : nums)
        {
            if (sum > 0)
                sum += num;
            else
                sum = num;
            res = max(res, sum);
        }
        return res;
    }

  private:
    int divide(vector<int> &nums, int left, int right)
    {
        if (left == right)
            return nums[left];
        int center = (left + right) / 2;
        int maxLeftSum = divide(nums, left, center);
        int maxRightSum = divide(nums, center + 1, right);

        int leftBorderSum = 0x80000000, tmpleft = 0;
        for (int i = center; i >= left; i--)
        {
            tmpleft = tmpleft + nums[i];
            if (tmpleft > leftBorderSum)
                leftBorderSum = tmpleft;
        }

        int rightBorderSum = 0x80000000, tmpright = 0;
        for (int i = center; i <= right + 1; i++)
        {
            tmpright = tmpright + nums[i];
            if (tmpright > rightBorderSum)
                rightBorderSum = tmpright;
        }
        return max({maxLeftSum, maxRightSum, leftBorderSum + rightBorderSum});
    }
};

int main(int argc, char const *argv[])
{
    vector<int> test{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    Solution solu;
    int res = solu.maxSubArray(test);
    cout << res << endl;
    return 0;
}
