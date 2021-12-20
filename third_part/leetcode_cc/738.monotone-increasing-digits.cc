#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int monotoneIncreasingDigits(int n)
    {
        string res = to_string(n);
        int flag;
        for (int i = res.size() - 1; i > 0; i--) {
            if (res[i - 1] > res[i]) {
                res[i - 1]--;
                flag = i;
            }
        }
        for (int j = flag; j < res.size(); j++) {
            res[j] = '9';
        }
        return stoi(res);
    }
};

int main(int argc, const char** argv)
{
    Solution so;
    int res = so.monotoneIncreasingDigits(332);
    cout << res << endl;
    return 0;
}