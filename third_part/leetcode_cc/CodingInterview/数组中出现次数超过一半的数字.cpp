#include <iostream>
#include <vector>

using namespace std;

bool CheckMoreThanHalf(vector<int> &nums, int number)
{
    int count = 0;
    for (auto num : nums)
    {
        if (num == number)
            ++count;
    }
    if (count * 2 > nums.size())
        return true;
    return false;
}

int MoreThanHalfNum(vector<int> &nums)
{
    if (nums.empty())
        return 0;
    int tmp = nums[0], times = 1;
    for (auto num : nums)
    {
        if (num == tmp)
            ++times;
        else if (num != tmp && times > 0)
            --times;
        else
        {
            tmp = num;
            times = 1;
        }
    }
    if (CheckMoreThanHalf(nums, tmp))
        return tmp;
    return 0;
}

int main(int argc, char const *argv[])
{
    vector<int> nums{1, 2, 3, 2, 4, 2, 5, 2, 3};
    int res = MoreThanHalfNum(nums);
    cout << res << endl;
    return 0;
}