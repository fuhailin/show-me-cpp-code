#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
   public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int result = 0;
        /*记录以当前数结尾的数组长度*/
        unordered_map<int, int> hashmap;
        for (int i : arr) {
            /*把以当前数结尾的长度，放入map中*/
            hashmap[i] = hashmap[i - difference] + 1;
            result = max(result, hashmap[i]);
        }
        return result;
    }
};

int main(int argc, char const* argv[]) {
    Solution so;
    vector<int> test = {1, 5, 7, 8, 5, 3, 4, 2, 1};
    int res = so.longestSubsequence(test, -2);
    cout << "res: " << res << endl;
    return 0;
}
