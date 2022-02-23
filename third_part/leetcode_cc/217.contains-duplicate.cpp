#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;
void show(vector<int> &a)
{
    for (int i = 0; i < 10; ++i)
        cout << a[i] << " ";
}

bool containsDuplicate_Sorting(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i - 1] == nums[i])
            return true;
    }
    return false;
}

bool containsDuplicate_HashTable(vector<int> &nums)
{
    unordered_set<int> set(nums.begin(), nums.end());
    return set.size() != nums.size();
}

int main(int argc, char const *argv[])
{
    vector<int> test{1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    bool res = containsDuplicate_HashTable(test);
    cout << boolalpha << res << endl;
    return 0;
}