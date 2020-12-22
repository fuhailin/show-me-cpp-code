#include <iostream>
#include <vector>
using namespace std;

class Solution
{
  public:
    int search(vector<int> &nums, int target)
    {
        if (nums.empty())
            return -1;
        else
            return help(nums, target, 0, nums.size() - 1);
    }

    int search_v2(vector<int> &nums, int target)
    {
        int left = 0, right = nums.size() - 1, mid = 0;
        while (left < right)
        {
            mid = (left + right) / 2;
            if (nums[mid] > nums[left])
                left = mid + 1;
            else
                right = mid;
        }
        if (nums[0] <= target && nums[mid] >= target)
        {
            left = 0;
            right = mid - 1;
        }
        else
        {
            left = mid;
            right = nums.size() - 1;
        }
        while (left <= right)
        {
            mid = (left + right) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

  private:
    int help(vector<int> &vec, int target, int left, int right)
    {
        while (left <= right)
        {
            int left = -1, right = -1;
            int rot = (left + right) / 2;
            if (vec[left] <= vec[rot])
            {
                if (vec[rot] >= target && vec[left] <= target)
                    left = binary_search(vec, target, left, rot);
                else
                    right = help(vec, target, rot + 1, right);
            }
            else
            {
                if (vec[rot + 1] <= target && vec[right] >= target)
                    right = binary_search(vec, target, rot + 1, right);
                else
                    left = help(vec, target, left, rot);
            }

            if (left == -1 && right == -1)
                return -1;
            else
            {
                if (left == -1)
                    return right;
                else
                    return left;
            }
        }
        return -1;
    }

    int binary_search(vector<int> &vec, int target, int left, int right)
    {
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (vec[mid] == target)
                return mid;
            else if (vec[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }
};

int main()
{
    vector<int> test{};
    int res = Solution().search_v2(test, 0);
    cout << res << endl;
}