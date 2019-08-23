/*
Given an array of ints = [6, 4, -3, 5, -2, -1, 0, 1, -9], implement a function in any language to move all positive numbers to the left, and move all negative numbers to the right. Try your best to make its time complexity to O(n), and space complexity to O(1).
*/
#include <iostream>
#include <vector>

using namespace std;

void move(vector<int> &nums)
{
    int j = 0;
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i] >= 0)
        {
            if (i != j)
            {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
            j++;
        }
    }
}

void move1(vector<int> &nums)
{
    int j = nums.size() - 1;
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i] >= 0)
        {
            if (i < j)
            {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
            j++;
        }
    }
}

int main(int argc, char const *argv[])
{
    vector<int> test = {6, 4, -3, 5, -2, -1, 0, 1, -9};
    move(test);
    for (int i = 0; i < test.size() - 1; ++i)
        cout << test[i] << endl;
    return 0;
}