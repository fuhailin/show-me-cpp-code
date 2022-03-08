#include <vector>
using namespace std;

class Solution {
  void Merge(vector<int>& nums, int left, int mid, int right) {
      
    ;
    ;
  }

  void MergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
      int mid = ((right - left) >> 1) + left;
      MergeSort(nums, left, mid);
      MergeSort(nums, mid + 1, right);
      Merge(nums, left, mid, right);
    }
  }

 public:
  vector<int> sortArray(vector<int>& nums) {
    MergeSort(nums, 0, nums.size() - 1);
    return nums;
  }
};