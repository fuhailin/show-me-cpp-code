#include <iostream>
#include <string>
using namespace std;
class Solution
{
  public:
    int strStr(string haystack, string needle)
    {
        if (needle == "")
            return 0;
        for (int i = 0; i <= (int(haystack.length()) - int(needle.length())); i++)
        {
            for (int j = 0; j < needle.length(); j++)
            {
                if (haystack[i + j] != needle[j])
                    break;
                if (j == needle.length() - 1)
                    return i;
            }
        }
        return -1;
    }
};

int main(int argc, char const *argv[])
{
    string test1, test2;
    cin >> test1 >> test2;
    Solution solu;
    int res = solu.strStr(test1, test2);
    cout << res;
    return 0;
}
