#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string addSpaces(string s, vector<int>& spaces)
    {
        int n = s.size();
        string res;
        res.reserve(n + spaces.size());
        int j = 0;
        for (int i = 0; i < s.size(); i++) {
            if (j < spaces.size() && i == spaces[j]) {
                res.push_back(' ');
                j++;
            }
            res.push_back(s[i]);
        }
        return res;
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    vector<int> test = { 1, 5, 7, 9 };
    string res = so.addSpaces("icodeinpython", test);
    cout << "res: " << res << endl;
    return 0;
}