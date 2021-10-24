#include <iostream>
#include <string>
using namespace std;

class Solution {
   public:
    string convertToTitle(int columnNumber) {
        string res;
        int rest = 0;
        while (columnNumber) {
            columnNumber--;
            rest = columnNumber % 26;
            columnNumber /= 26;
            if (rest == 0) {
                res += 'A';
            } else {
                res += 'A' + rest;
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    string res = so.convertToTitle(701);
    cout << "res: " << res << endl;
    return 0;
}