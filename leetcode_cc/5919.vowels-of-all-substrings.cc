#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    long long countVowels(string word) {
        string vowel = "aeiou";
        int n = word.size();
        const int MAXSIZE = 100000 + 1;
        long long dp[MAXSIZE]{};
        long long res = 0L;
        for (int i = 0; i < n; ++i) {
            if (vowel.find(word[i]) != string::npos) {
                dp[i + 1] = dp[i] + (i) + 1L;
            } else {
                dp[i + 1] = dp[i];
            }
            res += dp[i + 1];
        }
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;
    long long ans = s.countVowels("noosabasboosa");
    cout << ans << endl;
    return 0;
}
