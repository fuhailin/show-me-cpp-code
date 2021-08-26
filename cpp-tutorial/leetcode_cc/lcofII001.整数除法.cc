#include <climits>
#include <iostream>
using namespace std;

class Solution {
    long div(long a, long b) {
        cout << "a=" << a << "    b=" << b << endl;
        if (a < b) {
            return 0;
        }
        long res = 1, tb = b;
        while ((tb + tb) <= a) {
            tb += tb;
            res += res;
        }
        return res + div(a - tb, b);
    }

   public:
    int divide(int dividend, int divisor) {
        if (dividend == 0) return dividend;
        if (divisor == 1) return dividend;
        if (divisor == -1) {
            if (dividend > INT_MIN) return -dividend;
            return INT_MAX;
        }
        bool sign = true;
        long x = dividend, y = divisor;
        if ((x < 0 && y > 0) || (x > 0 && y < 0)) sign = false;
        if (x < 0) x = -x;
        if (y < 0) y = -y;

        long res = div(x, y);
        res = sign ? res : -res;
        if (res > INT_MAX || res < INT_MIN) return INT_MAX;
        return (int)res;
    }
};

int main(int argc, char const *argv[]) {
    Solution s;
    int res = s.divide(-2147483648, -1);
    cout << "res:" << res << endl;
    return 0;
}
