/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      Sort in C++
=============================================================================*/
#include <iostream>
#include <vector>

using namespace std;

class Sort
{
private:
  // A utility function to swap two elements
  void swap(int *a, int *b);
  // partition for quick sort
  int QuickSort_partition(vector<int> &arr, int left, int right);

public:
  /*  折半插入排序  */
  void HalfInsertSort(vector<int> &arr, int n);
  /*  直接插入排序  */
  void InsertSort(vector<int> &arr, int count);
  /* Selection Sort */
  void SectionSort(vector<int> &arr, int count);
  /*  冒泡排序  */
  void BubbleSort(vector<int> &arr, int count);
  /*  快速排序  */
  void QuickSort(vector<int> &arr, int left, int right);
 

  /*  归并排序  */
  void MergeSort()

};
