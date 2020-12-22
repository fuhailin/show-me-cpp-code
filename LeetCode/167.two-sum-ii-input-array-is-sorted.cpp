#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        vector<int> res;
        int i = 0, j = numbers.size() - 1;
        while (i < j)
        {
            int tmp = numbers[i] + numbers[j];
            if (tmp == target)
            {
                return vector<int>({i + 1, j + 1});
            }
            else if (tmp < target)
                i++;
            else
                j--;
        }
        return res;
    }

    vector<int> twoSum_HashMap(vector<int> &numbers, int target)
    {
        vector<int> res;
        unordered_map<int, int> hash;
        for (int i = 0; i < numbers.size(); i++)
        {
            if (hash.find(target - numbers[i]) != hash.end())
            {
                res.push_back(i + 1);
                res.push_back(hash[(target - numbers[i])] + 1);
                sort(res.begin(), res.end());
                return res;
            }
            else
            {
                hash[numbers[i]] = i;
            }
        }
        return res;
    }
    vector<int> twoSum_BruteForce(vector<int> &numbers, int target)
    {
        vector<int> res;
        for (int i = 0; i < numbers.size() - 1; i++)
        {
            for (int j = i + 1; j < numbers.size(); j++)
            {
                if ((numbers[i] + numbers[j]) == target)
                {
                    res.push_back(i + 1);
                    res.push_back(j + 1);
                    return res;
                }
                if ((numbers[i] + numbers[j]) > target)
                    break;
            }
        }
        return res;
    }
};
int main()
{
    vector<int> test = {2, 7, 11, 15};
    vector<int> res = Solution().twoSum(test, 9);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }
    return 0;
}