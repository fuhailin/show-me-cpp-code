#include <iostream>
using namespace std;

int sum(int i)
{
    if (i == 1 || i == 2)
        return 0;
    if (i == 3)
    {
        return 1;
    }
    if (i == 4)
    {
        return 2;
    }
    else
        return sum(i - 1) + sum(i - 2);
}

int main()
{
    int n;
    cin >> n;

    return 0;
}