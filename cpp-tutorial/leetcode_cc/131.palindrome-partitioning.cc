#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
    vector<vector<string>> res;

   public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while (i <= j) {
            if (s[i] != s[j]) return false;
            i++;
            --j;
        }
        return true;
    }
    vector<vector<string>> partition(string s) {
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    string test = "aba";
    bool res = so.isPalindrome(test);
    cout << "res: " << res << endl;
}
