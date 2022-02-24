#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

class Solution {
   public:
    string convertToBase7(int num) {
        if (!num) return "0";
        bool flag = false;
        if (num < 0) {
            num = -num;
            flag = true;
        }
        string res;
        int carry = 0, rest = 0;
        while (num) {
            rest = num % 7;
            num /= 7;
            if (rest == 0) {
                res += '0';
            } else {
                res += '0' + rest;
            }
        }
        reverse(res.begin(), res.end());
        if (flag) return "-" + res;
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    string res = so.convertToBase7(-100);
    cout << "res: " << res << endl;
    return 0;
}
