#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    string getHint(string secret, string guess) {
        int bulls = 0, cows = 0;
        unordered_map<char, int> set1, set2;
        for (int i = 0; i < secret.size(); i++) {
            if (secret[i] == guess[i]) {
                bulls++;
            } else {
                set1[secret[i]]++;
                set2[guess[i]]++;
            }
        }

        for (auto x : set1) {
            cows += min(set2[x.first], s.second);
        }
        return to_string(bulls) + "A" + to_string(cows) + "B";
    }
};