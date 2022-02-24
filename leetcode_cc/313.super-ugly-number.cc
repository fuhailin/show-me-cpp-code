class Solution {
   public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        int size = primes.size();
        vector<int> pointer(size, 1);
        vector<int> cache(size, 1);
        for (int i = 2; i <= n; ++i) {
            int min_t = INT_MAX;
            for (int j = 0; j < size; ++j) {
                cache[j] = dp[pointer[j]] * primes[j];
                min_t = min(cache[j], min_t);
            }
            dp[i] = min_t;
            for (int j = 0; j < size; ++j) {
                if (dp[i] == cache[j]) {
                    pointer[j]++;
                }
            }
        }
        return dp[n];
    }
};

