#include <iostream>
#include <vector>
using namespace std;
void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
{
    int length = m + n;
    while (length > 0)
    {
        if (m == 0)
        {
            nums1[length - 1] = nums2[n - 1];
            n--;
        }

        else if (n == 0)
        {
            break;
        }
        else
        {
            if (nums1[m - 1] >= nums2[n - 1])
            {
                nums1[length - 1] = nums1[m - 1];
                m--;
            }
            else
            {
                nums1[length - 1] = nums2[n - 1];
                n--;
            }
        }
        length--;
    }
}
int main(int argc, char const *argv[])
{
    vector<int> nums1{1, 2, 3, 0, 0, 0};
    vector<int> nums2{2, 5, 6};
    merge(nums1, 3, nums2, 3);
    return 0;
}