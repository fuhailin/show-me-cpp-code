#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void print_vec(vector<int>& nums) {
  for (int i = 0; i < nums.size(); i++) {
    if (i == nums.size() - 1)
      cout << nums[i] << endl;
    else
      cout << nums[i] << " ";
  }
}

void move(vector<int>& nums, int M) {
  M = M % nums.size();
  reverse(nums.begin(), nums.begin() + nums.size() - M);
  // print_vec(nums);
  reverse(nums.begin() + nums.size() - M, nums.end());
  // print_vec(nums);
  reverse(nums.begin(), nums.end());
}

int main(int argc, char const* argv[]) {
  int N, M;
  cin >> N >> M;
  vector<int> nums(N, 0);
  for (int i = 0; i < N; i++) {
    cin >> nums[i];
  }
  move(nums, M);
  print_vec(nums);
  return 0;
}