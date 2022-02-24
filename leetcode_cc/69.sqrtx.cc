#include <iostream>
using namespace std;

class Solution {
   public:
    int mySqrt(long x) {
        long left = -1, right = x + 1, mid;
        while (left + 1 != right) {
            mid = left + ((right - left) >> 1);
            long tmp = mid * mid;
            if (tmp <= x) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return left;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.mySqrt(8);
    cout << "res: " << res << endl;
    return 0;
}
