#include <iostream>
#include <vector>
#include <math.h>
#include <set>
using namespace std;

float distance(pair<float, float> pointA, pair<float, float> pointB)
{
    float dis = pow((pointA.first - pointB.first), 2) + pow((pointA.second - pointB.second), 2);
    return dis;
}
bool Equal(float num1, float num2)
{
    if (fabs(num1 - num2) < 0.000001)
        return true;
    else
        return false;
}
bool validSquare(vector<pair<float, float>> points)
{
    set<float> _set;
    for (int i = 0; i < points.size() - 1; i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            _set.insert(distance(points[i], points[j]));
        }
    }
    if (_set.size() == 2)
    {
        if (*_set.begin() == 0)
            return false;
        else
        {
            float a = 2 * (*_set.begin());
            float b = *_set.rbegin();
            return Equal(a, b);
        }
    }
    else
    {
        return false;
    }
}

int main()
{
    //pair<float, float> a(-1, 0);
    //pair<float, float> b(1, 0);
    //pair<float, float> c(0, 1);
    //pair<float, float> d(0, -1);

    /*pair<float, float> a(1134, -2539);
	pair<float, float> b(492, -1255);
	pair<float, float> c(-792, -1897);
	pair<float, float> d(-150, -3181);*/

    pair<float, float> a(0, 0);
    pair<float, float> b(1, 1);
    pair<float, float> c(1, 0);
    pair<float, float> d(1, 1);

    vector<pair<float, float>> points{a, b, c, d};
    cout << boolalpha << validSquare(points) << endl;
    return 0;
}