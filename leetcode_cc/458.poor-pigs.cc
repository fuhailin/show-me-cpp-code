#include <math.h>

#include <iostream>
using namespace std;

class Solution {
   public:
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int n = minutesToTest / minutesToDie + 1;
        int pigs = ceil(log(buckets) / log(n));
        return pigs;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    int res = so.poorPigs(1000, 15, 60);
    cout << res << endl;
    return 0;
}
