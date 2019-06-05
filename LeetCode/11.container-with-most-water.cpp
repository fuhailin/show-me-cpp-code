#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Solution
{
public:
    int maxArea_Brute_Force(vector<int> &height)
    {
        int res = 0;
        for (int i = 0; i < height.size(); i++)
        {
            for (int j = i + 1; j < height.size(); j++)
            {
                res = max(min(height[i], height[j]) * (j - i), res);
            }
        }
        return res;
    }

    int maxArea(vector<int> &height)
    {
        int res = 0, l = 0, r = height.size() - 1;
        while (l < r)
        {
            res = max(min(height[l], height[r]) * (r - l), res);
            if (height[l] < height[r])
                ++l;
            else
                --r;
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> test = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int res = Solution().maxArea(test);
    cout << res << endl;
    return 0;
}