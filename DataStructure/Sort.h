/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      Sort in C++
=============================================================================*/
#include <iostream>

using namespace std;

class Sort
{
private:
  // A utility function to swap two elements
  void swap(int *a, int *b);
  // partition for quick sort
  int partition(int arr[], int left, int right);

public:
  /*  折半插入排序  */
  void HalfInsertSort(int R[], int n);
  /*  直接插入排序  */
  void InsertSort(int arr[], int count);
  /* Selection Sort */
  void SectionSort(int arr[], int count);
  /*  冒泡排序  */
  void BubbleSort(int arr[], int count);
  /*  快速排序  */
  void QuickSort(int arr[], int left, int right);
  /* Function to print an array */
  void printArray(int arr[], int count);
};
