#include <iostream>
#include <vector>
#include <stack>
#include <string>
// #include <cstdlib>

using namespace std;

string hex2ascii(string hex)
{
    int len = hex.length();
    std::string newString;
    for (int i = 0; i < len; i += 2)
    {
        string byte = hex.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), NULL, 16);
        newString.push_back(chr);
    }
    return newString;
}

std::string urlDecode(std::string &eString)
{
    stack<char> s;
    string newstr;
    for (int i = eString.size() - 1; i >= 0; i--)
    {
        char tmp = eString[i];
        if (tmp == '%')
        {

            newstr.push_back(s.top());
            s.pop();
            newstr.push_back(s.top());
            s.pop();
            
            newstr = hex2ascii(newstr);
            s.push(newstr[0]);
            newstr.clear();
        }
        else
        {
            s.push(tmp);
        }
    }
    while (!s.empty())
    {
        newstr.push_back(s.top());
        s.pop();
    }
    return newstr;
}

vector<string> url_decode(vector<string> strs)
{
    vector<string> res;
    for (int i = 0; i < strs.size(); i++)
    {
        string str1 = strs[i];
        string str2 = urlDecode(str1);
        res.push_back(str2);
    }
    return res;
}

int main(int argc, char const *argv[])
{
    int T;
    cin >> T;
    vector<string> test;
    for (int i = 0; i < T; i++)
    {
        string str;
        cin >> str;
        test.push_back(str);
    }
    vector<string> res = url_decode(test);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << endl;
    }

    return 0;
}