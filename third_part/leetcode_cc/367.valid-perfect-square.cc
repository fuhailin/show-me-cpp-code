#include <iostream>
using namespace std;

class Solution {
   public:
    bool isPerfectSquare(long num) {
        if (num == 1) return true;
        long left = 1, right = num >> 1, mid;
        while (left <= right) {
            mid = left + ((right - left) >> 1);
            long tmp = mid * mid;
            if (tmp > num) {
                right = mid - 1;
            } else if (tmp < num) {
                left = mid + 1;
            } else {
                return true;
            }
        }
        return false;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    bool res = so.isPerfectSquare(16);
    cout << "res: " << boolalpha << res << endl;
    return 0;
}
