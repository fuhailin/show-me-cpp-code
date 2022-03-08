#include "merge_sort.h"
namespace Sort {

template <typename T>
void MergeSort<T>::mergeSort(vector<T>& nums, int l, int r) {
  if (l >= r) return;
  int mid = (l + r) >> 1;
  mergeSort(nums, l, mid);
  mergeSort(nums, mid + 1, r);
  int i = l, j = mid + 1;
  int cnt = 0;
  while (i <= mid && j <= r) {
    if (nums[i] <= nums[j]) {
      _tmp[cnt++] = nums[i++];
    } else {
      _tmp[cnt++] = nums[j++];
    }
  }
  while (i <= mid) {
    _tmp[cnt++] = nums[i++];
  }
  while (j <= r) {
    _tmp[cnt++] = nums[j++];
  }
  for (int i = 0; i < r - l + 1; ++i) {
    nums[i + l] = _tmp[i];
  }
}

template <typename T>
vector<T> MergeSort<T>::sortArray(vector<T>& nums) {
  _tmp.resize((T)nums.size(), 0);
  mergeSort(nums, 0, (T)nums.size() - 1);
  return nums;
}

// Explicitly instantiate only the classes you want to be defined.
template class MergeSort<int>;
template class MergeSort<double>;

}  // namespace Sort