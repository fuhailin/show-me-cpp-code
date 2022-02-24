#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> num = {1, 2, 3, 4, 5, 6};
    int length = num.size();

    vector<int>::const_iterator begin = num.begin();
    vector<int>::const_iterator last = num.begin() + 3;
    vector<int> new_arr(begin, last);

    vector<int>::const_iterator begin1 = num.end() - 3;
    vector<int>::const_iterator last1 = num.end();
    vector<int> new_arr1(begin1, last1);

    for (int i = 0; i < new_arr1.size(); i++)
    {
        cout << new_arr1[i] << " ";
    }

    return 0;
}
