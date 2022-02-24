#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution
{
  public:
    string longestCommonPrefix(vector<string> &strs)
    {
        if (strs.size() == 0)
        {
            return "";
        }
        for (int i = 0; i < strs[0].size(); i++)
        {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); j++)
            {
                if (i == strs[j].size() || strs[j][i] != c)
                {
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};

int main(int argc, char const *argv[])
{
    // vector<string> strs = {"flower", "flow", "flight"};
    vector<string> strs = {"dog"};
    // vector<string> strs = {"dog", "racecar", "car"};
    Solution solu;
    string res = solu.longestCommonPrefix(strs);
    cout << res << endl;
    return 0;
}
