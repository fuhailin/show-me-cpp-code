#include "bits/stdc++.h"

class Solution {
    unordered_map<int, int> memo;

   public:
    int integerReplacement(int n) {
        if (n == 1)
            return 0;
        else if (memo.count(n)) {
            return memo[n];
        } else if (n % 2 == 0) {
            return memo[n] = 1 + integerReplacement(n >> 1);
        } else {
            return memo[n] = 2 + min(integerReplacement((n >> 1) + 1), integerReplacement(n >> 1));
        }
    }
};