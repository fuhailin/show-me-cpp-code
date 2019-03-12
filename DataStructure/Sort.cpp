/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      Sort in C++
=============================================================================*/
#include <iostream>
#include <vector>
#include "Sort.h"
using namespace std;

/*  折半插入排序  */
void Sort::HalfInsertSort(vector<int> &nums, int n)
{
    int i, j, head, rear, mid, tmp;
    for (i = 1; i < n; ++i)
    {
        tmp = nums[i];
        head = 0;
        rear = i;
        while (rear > head)
        {
            mid = (head + rear) / 2;
            if (tmp > nums[mid])
                head = mid + 1;
            else
                rear = mid - 1;
        }
        for (j = i - 1; j >= rear + 1; --j)
        {
            nums[j] = nums[j - 1];
        }
        nums[j + 1] = tmp;
    }
}
/*  直接插入排序  */
void Sort::InsertSort(vector<int> &nums, int count)
{
    int temp;
    for (int i = 1; i < count; ++i)
    {
        temp = nums[i];
        for (int j = i; j >= 0; --j)
        {
            while (j >= 0 && temp < nums[j - 1])
            {
                nums[j] = nums[j - 1];
                --j;
            }
            nums[j] = temp;
        }
    }
}
/* Selection Sort */
void Sort::SectionSort(vector<int> &nums, int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int minIndex = i;
        for (int j = i; j < count - 1; j++)
        {
            if (nums[j + 1] < nums[j])
                minIndex = j + 1;
        }
        swap(&nums[i], &nums[minIndex]);
    }
}
/*  冒泡排序  */
void Sort::BubbleSort(vector<int> &nums, int count)
{
    int flag;
    for (int i = 0; i < count; ++i)
    {
        flag = true;
        for (int j = count - 1; j > i; --j)
        {
            if (nums[j - 1] > nums[j])
            {
                swap(&nums[j - 1], &nums[j]);
                flag = false;
            }
            if (flag)
                break;
        }
    }
}
/*  快速排序  */
void Sort::QuickSort(vector<int> &nums, int left, int right)
{
    if (left < right)
    {
        int pivot = QuickSort_partition(nums, left, right);
        QuickSort(nums, left, pivot - 1);
        QuickSort(nums, pivot + 1, right);
    }
}

void Sort::swap(int *a, int *b)
{
    if (*a != *b)
    {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

int Sort::QuickSort_partition(vector<int> &nums, int left, int right)
{
    int pivot = nums[left];
    while (left < right)
    {
        while (left < right && nums[right] >= pivot)
            --right;
        nums[left] = nums[right];
        while (left < right && nums[left] <= pivot)
            ++left;
        nums[right] = nums[left];
    }
    nums[left] = pivot;
    return left;
}

/* Function to print an array */
void Sort::printArray(vector<int> &nums, int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << nums[i] << ' ';
    }
}

int main()
{
    vector<int> nums{9, 8, 7, 6, 5, 4, 3, 2, 1, 9};
    Sort sort;
    sort.InsertSort(nums, nums.size() - 1);
    sort.QuickSort(nums, 0, nums.size() - 1);
    sort.HalfInsertSort(nums, nums.size() - 1);
    sort.BubbleSort(nums, nums.size() - 1);
    sort.SectionSort(nums, nums.size() - 1);
    sort.printArray(nums, nums.size());
    return 0;
}