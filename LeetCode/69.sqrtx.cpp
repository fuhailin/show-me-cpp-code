#include <iostream>

using namespace std;
int mySqrt(int x)
{
    long r = 0;
    while (r * r < x)
        if (!r)
            r++;
        else
            r = r + x / r;
    return r;
}
int main(int argc, char const *argv[])
{
    int res = mySqrt(8);
    cout << res << endl;
    return 0;
}