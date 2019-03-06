/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/lines-intersection/
#  Email:            hailinfufu@outlook.com
#  Description:      求折线段与直线的交点数/
=============================================================================*/

#include <iostream>
#include <vector>
using namespace std;

int getSection(vector<int> vec, int val)
{
    int sum = 0;
    int flag = vec[0] - val;
    for (int i = 0; i < vec.size(); i++)
    {
        if ((vec[i] - val) * flag <= 0)
        {
            sum++;
            flag = vec[i] - val;
        }
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    vector<int> test{5, 3, 1, 4};
    int res = getSection(test, 2);
    cout << res << endl;
    return 0;
}