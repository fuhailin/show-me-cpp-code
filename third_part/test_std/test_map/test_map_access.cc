

#include <iostream>
#include <iterator>
#include <unordered_map>


using namespace std;

int main() {
    unordered_map<int, int> cache;
    cache[0];
    cout << cache.size() << ", " << cache[0] << endl;
    return 0;
}
