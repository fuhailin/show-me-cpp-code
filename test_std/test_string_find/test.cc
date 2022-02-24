#include <iostream>
#include <string>
using namespace std;

// Driver code
int main() {
    std::string str1("0123456789");
    std::string str2("5");

    int res = str1.find(str2, 1);
    cout << "str1 is: " << str1 << "\nstr2 is: " << str2 << endl;
    cout << "res :" << res << endl;
    return 0;
}
