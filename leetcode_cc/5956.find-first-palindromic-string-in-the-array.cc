#include <string>
#include <vector>
using namespace std;

class Solution {
    bool isPalindrome(const string& s)
    {
        int left = 0, right = s.size() - 1;
        while (left < right)
        {
            if (s[left] != s[right])
                return false;
            left++;
            right--;
        }
        return true;
    }

public:
    string firstPalindrome(vector<string>& words)
    {
        string res;
        for (auto& word : words)
        {
            if (isPalindrome(word))
            {
                return word;
            }
        }
        return "";
    }
};

