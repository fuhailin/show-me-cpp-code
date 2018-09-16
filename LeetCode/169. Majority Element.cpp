#include <iostream>
#include <vector>
using namespace std;
int majorityElement(vector<int> &nums)
{
    int res = 0, n = nums.size();
    for (int i = 0; i < 32; ++i)
    {
        int ones = 0, zeros = 0;
        for (int num : nums)
        {
            if (ones > n / 2 || zeros > n / 2)
                break;
            if ((num & (1 << i)) != 0)
                ++ones;
            else
                ++zeros;
        }
        if (ones > zeros)
            res |= (1 << i);
    }
    return res;
}

int main()
{
    vector<int> a = {8, 1, 1, 8, 1, 1, 6, 1, 5, 8, 8};
    int m = majorityElement(a);
    cout << m << endl;
    return 0;
}