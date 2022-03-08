#include "quick_sort.h"
namespace Sort {

template <typename T>
void QuickSort<T>::randomized_quicksort(vector<T>& nums, int l, int r) {
  if (l < r) {
    int pos = randomized_partition(nums, l, r);
    randomized_quicksort(nums, l, pos - 1);
    randomized_quicksort(nums, pos + 1, r);
  }
}

template <typename T>
int QuickSort<T>::partition(vector<T>& nums, int l, int r) {
  int pivot = nums[r];
  int i = l - 1;
  for (int j = l; j <= r - 1; ++j) {
    if (nums[j] <= pivot) {
      i = i + 1;
      swap(nums[i], nums[j]);
    }
  }
  swap(nums[i + 1], nums[r]);
  return i + 1;
}

template <typename T>
int QuickSort<T>::randomized_partition(vector<T>& nums, int l, int r) {
  int i = rand() % (r - l + 1) + l;  // 随机选一个作为我们的主元
  swap(nums[r], nums[i]);
  return partition(nums, l, r);
}

// Explicitly instantiate only the classes you want to be defined.
template class QuickSort<int>;
template class QuickSort<double>;

}  // namespace Sort