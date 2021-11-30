#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
   public:
    int distributeCandies(vector<int>& candyType) {
        int n = candyType.size() / 2;
        unordered_set<int> hashmap(candyType.begin(), candyType.end());
        int i = 0;
        while (hashmap.size() < n && i < candyType.size()) {
            hashmap.insert(candyType[i]);
            i++;
        }
        return hashmap.size();
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 1, 2, 3};
    int res = so.distributeCandies(test);
    cout << "res: " << res << endl;
    return 0;
}
