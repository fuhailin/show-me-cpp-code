#include <iostream>
using namespace std;

int main(int argc, char const *argv[]) {
    long long s;
    int n;
    while (cin >> s >> n) {
        long long res = 1;
        for (int i = 1; i <= n; i++) {
            res *= s;
        }
        cout << res << endl;
    }
    return 0;
}
