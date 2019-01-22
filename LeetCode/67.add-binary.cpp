#include <iostream>
#include <string>

using namespace std;
string addBinary(string a, string b)
{
    int bigger = max(a.size(), b.size());
    int carry = 0;
    string result = "";
    int tmp;
    for (int i = 1; i <= bigger; i++)
    {
        if (i > a.size())
        {
            tmp = int(b[-1 * i]) + carry;
            if (tmp == 2)
            {
                carry = 1;
                tmp = 0;
            }
            else
                carry = 0;
        }
        else if (i > b.size())
        {
            tmp = int(a[-1 * i]) + carry;
            if (tmp == 2)
            {
                carry = 1;
                tmp = 0;
            }
            else
                carry = 0;
        }
        else
        {
            tmp = int(a[-1 * i]) + int(b[-1 * i]) + carry;
            if (tmp == 2)
            {
                carry = 1;
                tmp = 0;
            }
            else if (tmp == 3)
            {
                carry = 1;
                tmp = 1;
            }
            else
                carry = 0;
        }
        result = to_string(tmp) + result;
    }
    if (carry)
        result = to_string(carry) + result;
    return result;
}

int main(int argc, char const *argv[])
{
    string res = addBinary("1010", "1011");
    cout << res << endl;
    return 0;
}