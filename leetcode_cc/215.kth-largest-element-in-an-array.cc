#include <iostream>
#include <vector>
using namespace std;

class Solution {
    // int parition(vector<int>& nums, int low, int high) {
    //     int pivot = nums[high];

    // }
    int partition(vector<int>& nums, int left, int right) {
        int pivot = nums[left];  //初始化一个待比较数据
        int i = left, j = right;
        while (i < j) {
            while (i < j && nums[j] >= pivot) {  //#从后往前查找，直到找到一个比pivot更小的数
                j -= 1;
            }
            nums[i] = nums[j];                   // #将更小的数放入左边
            while (i < j && nums[i] <= pivot) {  //从前往后找，直到找到一个比pivot更大的数
                i += 1;
            }
            nums[j] = nums[i];  // 将更大的数放入右边
            // 循环结束，i与j相等
        }
        nums[i] = pivot;  //待比较数据放入最终位置
        return i;         //返回待比较数据最终位置
    }

    void quickSort(vector<int>& nums, int low, int high) {
        if (low < high) {
            int pivot = partition(nums, low, high);
            quickSort(nums, low, pivot - 1);
            quickSort(nums, pivot + 1, high);
        }
    }

   public:
    int findKthLargest(vector<int>& nums, int k) {
    }
};