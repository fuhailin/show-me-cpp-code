/* A Naive recursive implementation of 0-1 Knapsack problem */
#include <algorithm>
#include <iostream>
using namespace std;

// Returns the maximum value that can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n) {
  // Base Case
  if (n == 0 || W == 0) return 0;

  // If weight of the nth item is more than Knapsack capacity W, then
  // this item cannot be included in the optimal solution
  if (wt[n - 1] > W) return knapSack(W, wt, val, n - 1);

  // Return the maximum of two cases:
  // (1) nth item included
  // (2) not included
  else
    return max(val[n - 1] + knapSack(W - wt[n - 1], wt, val, n - 1),
               knapSack(W, wt, val, n - 1));
}

// Driver program to test above function
int main() {
  int val[] = {60, 100, 120};  // 价值
  int wt[] = {10, 20, 30};     // 重量
  int W = 50;                  //背包的总capacity
  int n = sizeof(val) / sizeof(val[0]);
  cout << knapSack(W, wt, val, n) << endl;
  return 0;
}