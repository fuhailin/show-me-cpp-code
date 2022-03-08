#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <vector>
using namespace std;

namespace Sort {
/*
// 整數或浮點數皆可使用,若要使用物件(class)時必須設定"小於"(<)的運算子功能
*/
template <typename T>
class MergeSort {
 private:
  vector<T> _tmp;

  void mergeSort(vector<T>& nums, int l, int r);

 public:
  vector<T> sortArray(vector<T>& nums);
};

}  // namespace Sort

#endif  // MERGE_SORT_H
