#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution
{
  public:
    bool isValid(string s)
    {
        stack<char> stk;
        // Probably, when you don't use '&', for(char c : s) will case copy operation to give c a value.
        // But when you use '&', c is just a reference of s[I], therefore, no more copy function, save the time.
        for (const auto &c : s)
        {
            switch (c)
            {
            case '(':
                stk.push(c);
                break;
            case '[':
                stk.push(c);
                break;
            case '{':
                stk.push(c);
                break;
            case ')':
                if (!stk.empty() && stk.top() == '(')
                {
                    stk.pop();
                }
                else
                {
                    return false;
                }
                break;
            case ']':
                if (!stk.empty() && stk.top() == '[')
                {
                    stk.pop();
                }
                else
                {
                    return false;
                }
                break;
            case '}':
                if (!stk.empty() && stk.top() == '{')
                {
                    stk.pop();
                }
                else
                {
                    return false;
                }
                break;
            }
        }
        return stk.empty();
    }
};

int main(int argc, char const *argv[])
{
    // string s = "()[]{}";
    string s = "([)]";
    Solution solu;
    bool res = solu.isValid(s);
    cout << boolalpha << res << endl;
    return 0;
}
