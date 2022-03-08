#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <vector>
using namespace std;

namespace Sort {
/*
// 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
*/
template <typename T>
class QuickSort {
 private:
  int partition(vector<T>& nums, int l, int r);

  int randomized_partition(vector<T>& nums, int l, int r);

  void randomized_quicksort(vector<T>& nums, int l, int r);

 public:
  vector<T> sortArray(vector<T>& nums);
};

}  // namespace Sort

#endif  // QUICK_SORT_H
