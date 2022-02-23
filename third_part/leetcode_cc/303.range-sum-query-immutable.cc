#include <vector>

using namespace std;

class NumArray {
  vector<int> preSum;

 public:
  NumArray(vector<int>& nums) {
    const int N = nums.size();
    preSum.resize(N + 1);
    for (int i = 0; i < N; ++i) {
      preSum[i + 1] = preSum[i] + nums[i];
    }
  }

  int sumRange(int left, int right) { return preSum[right + 1] - preSum[left]; }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */