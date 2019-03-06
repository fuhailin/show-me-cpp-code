#include <iostream>
#include <vector>
using namespace std;
void reverseString(vector<char> &s)
{
    char tmp;
    int l = 0, r = s.size() - 1;
    while (l < r)
    {
        tmp = s[l];
        s[l] = s[r];
        s[r] = tmp;
        l++;
        r--;
    }
}
int main(int argc, char const *argv[])
{
    vector<char> test{'h', 'e', 'l', 'l', 'o'};
    reverseString(test);
    for (int i = 0; i < test.size(); i++)
    {
        cout << test[i];
    }
    return 0;
}