#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int maxNumberOfBalloons(string text) {
        unordered_map<char, int> dict;
        for(char c : text) {
            dict[c]++;
        }
        int b = dict['b'];
        int a = dict['a'];
        int l = dict['l'] / 2;
        int o = dict['o'] / 2;
        int n = dict['n'];
        return min(b, min(a, min(l, min(o, n))));
    }
};