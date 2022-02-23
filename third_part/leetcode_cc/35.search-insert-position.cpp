#include <iostream>
#include <vector>
using namespace std;
class Solution
{
  public:
    int searchInsert(vector<int> &nums, int target)
    {
        int i = 0;
        for (; i < nums.size(); i++)
        {
            if (nums[i] >= target)
                return i;
        }
        return i;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> test = {1, 3, 5, 6};
    Solution solu;
    int res = solu.searchInsert(test, 2);
    cout << res << endl;
    return 0;
}
