#include <iostream>
#include <vector>
#include <algorithm>
#include<unordered_map>

using namespace std;
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; ++i)
        {
            for (int j = i + 1; j < nums.size() - 1; ++j)
            {
                for (int k = j + 1; k < nums.size(); ++k)
                {
                    if ((nums[i] + nums[j] + nums[k]) == 0)
                    {
                        vector<int> tmp;
                        tmp.push_back(nums[i]);
                        tmp.push_back(nums[j]);
                        tmp.push_back(nums[k]);
                        res.push_back(tmp);
                    }
                }
            }
        }
        res.erase(unique(res.begin(), res.end()), res.end());
        return res;
    }

private:
    vector<vector<int>> twoSum(vector<int> &nums, int target)
    {
        
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}