#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool isPalindrome(const string& s, int startIndex, int endIndex) {
//        if (endIndex - startIndex < 5) return false;
        unordered_map<char, int> hashmap;
        for (int i = startIndex; i <= endIndex; i++) {
            char c = s[i];
            if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u') {
                return false;
            }
            hashmap[c]++;
        }
        return hashmap['a'] && hashmap['e'] && hashmap['i'] && hashmap['o'] && hashmap['u'];
    }

    int countVowelSubstrings(string word) {
        int len, ans = 0;
        if (word.empty() || (len = word.length()) < 5) return 0;
        cout << "len: " << len << endl;
        //dp[i][j]：s字符串下标i到下标j的字串是否是一个回文串，即s[i, j]
        vector<vector<bool>> dp(len, vector<bool>(len, false));
        for (int j = 0; j < len; j++) {
            for (int i = 0; i <= j; i++) {
                //当两端字母一样时，才可以两端收缩进一步判断
                if ((word[i] == 'a' || word[i] == 'e' || word[i] == 'i' || word[i] == 'o' || word[i] == 'u') && j -i >= 4) {
                    //i++，j--，即两端收缩之后i,j指针指向同一个字符或者i超过j了,必然是一个回文串
                    if(isPalindrome(word, i, j)) {
                        dp[i][j] = true;
                    } else {
                        //否则通过收缩之后的字串判断
                        dp[i][j] = dp[i + 1][j];
                    }
                } else {  //两端字符不一样，不是回文串
                    dp[i][j] = false;
                }
            }
        }
        //遍历每一个字串，统计回文串个数
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (dp[i][j]) ans++;
            }
        }
        return ans;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    int res = so.countVowelSubstrings("eeiou");
    cout << "res: " << res << endl;
    // cout << boolalpha << so.isPalindrome("cuaieuouac") << endl;
    return 0;
}
