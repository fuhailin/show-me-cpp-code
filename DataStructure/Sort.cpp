/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      Sort in C++
=============================================================================*/
#include <iostream>
#include "Sort.h"
using namespace std;

/*  折半插入排序  */
void Sort::HalfInsertSort(int R[], int n)
{
    int i, j, head, rear, mid, tmp;
    for (i = 1; i < n; ++i)
    {
        tmp = R[i];
        head = 0;
        rear = i;
        while (rear > head)
        {
            mid = (head + rear) / 2;
            if (tmp > R[mid])
                head = mid + 1;
            else
                rear = mid - 1;
        }
        for (j = i - 1; j >= rear + 1; --j)
        {
            R[j] = R[j - 1];
        }
        R[j + 1] = tmp;
    }
}
/*  直接插入排序  */
void Sort::InsertSort(int arr[], int count)
{
    int temp;
    for (int i = 1; i < count; ++i)
    {
        temp = arr[i];
        for (int j = i; j >= 0; --j)
        {
            while (j >= 0 && temp < arr[j - 1])
            {
                arr[j] = arr[j - 1];
                --j;
            }
            arr[j] = temp;
        }
    }
}
/* Selection Sort */
void Sort::SectionSort(int arr[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        int minIndex = i;
        for (int j = i; j < count - 1; j++)
        {
            if (arr[j + 1] < arr[j])
                minIndex = j + 1;
        }
        swap(&arr[i], &arr[minIndex]);
    }
}
/*  冒泡排序  */
void Sort::BubbleSort(int arr[], int count)
{
    int flag;
    for (int i = 0; i < count; ++i)
    {
        flag = true;
        for (int j = count - 1; j > i; --j)
        {
            if (arr[j - 1] > arr[j])
            {
                swap(&arr[j - 1], &arr[j]);
                flag = false;
            }
            if (flag)
                break;
        }
    }
}
/*  快速排序  */
void Sort::QuickSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int pivot = partition(arr, left, right);
        QuickSort(arr, left, pivot - 1);
        QuickSort(arr, pivot + 1, right);
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

int Sort::partition(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = (left - 1);

    for (int j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(&arr[++i], &arr[j]);
        }
    }
    swap(&arr[++i], &arr[right]);
    return i;
}

/* Function to print an array */
void Sort::printArray(int arr[], int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << arr[i] << ' ';
    }
}

int main()
{
    int arr[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 9};
    int arrSize = sizeof(arr) / sizeof(arr[0]);
    Sort sort;
    // InsertSort(test, 10);
    sort.QuickSort(arr, 0, arrSize - 1);
    // HalfInsertSort(test, 10);
    // sort.BubbleSort(arr, arrSize);
    // sort.SectionSort(arr, arrSize);
    sort.printArray(arr, arrSize);
    return 0;
}