#include <iostream>
using namespace std;

class Solution {
    int happyNum(int num) {
        int sum = 0;
        while (num) {
            int base = num % 10;
            sum += base * base;
            num /= 10;
        }
        return sum;
    }

   public:
    bool isHappy(int n) {
        int fast = n, slow = n;
        do {
            fast = happyNum(fast);
            fast = happyNum(fast);
            slow = happyNum(slow);
        } while (fast != slow);
        return slow == 1;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    bool res = so.isHappy(2);
    cout << "res: " << boolalpha << res << endl;
    return 0;
}
