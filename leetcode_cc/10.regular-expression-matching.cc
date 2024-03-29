#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Solution {
 public:
  bool isMatch(string s, string p) {
    /**
     * f[i][j]: if s[0..i-1] matches p[0..j-1]
     * if p[j - 1] != '*'
     *      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
     * if p[j - 1] == '*', denote p[j - 2] with x
     *      f[i][j] is true if any of the following is true
     *      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
     *      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i -
     * 1][j]
     * '.' matches any single character
     */
    int m = s.size(), n = p.size();
    // dp[0][0]表示都为空串，所以dp数组要+1
    vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

    f[0][0] = true;
    for (int i = 1; i <= m; i++) f[i][0] = false;
    // p[0.., j - 3, j - 2, j - 1] matches empty if p[j - 1] is '*' and p[0..j -
    // 3] matches empty
    for (int j = 1; j <= n; j++)
      f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];

    for (int i = 1; i <= m; i++)
      for (int j = 1; j <= n; j++)
        if (p[j - 1] != '*')
          f[i][j] =
              f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
        else
          // p[0] cannot be '*' so no need to check "j > 1" here
          f[i][j] = f[i][j - 2] ||
                    (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

    return f[m][n];
  }


};

int main(int argc, char const* argv[]) {
  string s = "aa";
  string p = "a*";
  bool res = Solution().isMatch(s, p);
  cout << boolalpha << res << endl;
  return 0;
}