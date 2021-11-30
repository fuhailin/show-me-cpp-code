#include "bits/stdc++.h"

class Solution {
    vector<string> splitSentence(string str) {
        vector<string> res;
        string word = "";
        for (auto &x : str) {
            if (x == ' ') {
                if (!word.empty()) {
                    res.emplace_back(word);
                }
                word = "";
            } else {
                word = word + x;
            }
        }
        if (!word.empty()) {
            res.emplace_back(word);
        }
        return res;
    }

    bool isValid(string word) {
        int n = word.size();

        if (word[n - 1] == '!' || word[n - 1] == '.' || word[n - 1] == ',') {
            word = word.substr(0, n - 1);
        }
        int len = word.size();
        int num = 0;
        for (int i = 0; i < len; i++) {
            if (word[i] == '-') {
                num++;
                if (i == 0 || i == len - 1 || num > 1) {
                    return false;
                }
            } else if (word[i] < 'a' || word[i] > 'z') {
                return false;
            }
        }
        return true;
    }

   public:
    int countValidWords(string sentence) {
        int res = 0;
        vector<string> wordsList = splitSentence(sentence);
        for (auto &word : wordsList) {
            if (isValid(word)) {
                // cout << "valid word-> " << word << endl;
                res++;
            }
        }
        return res;
    }
};

int main(int argc, char const *argv[]) {
    Solution so;
    // string test = "cat and  dog";
    // string test = "!this  1-s b8d!";
    // string test = "bob and  bob are playing stone-game10";
    // string test = "he bought 2 pencils, 3 erasers, and 1  pencil-sharpener.";
    string test = "2xp!kh!j , aq 4vk ji , 4-cfb7 ic7 p q q9.po5.sw! z5 5 z 6 6e !  6ou5w";
    int res = so.countValidWords(test);
    // string word = ",";
    // bool res = so.isValid(word);
    // cout << word << " -> " << boolalpha << res << endl;
    cout << "res: " << res << endl;
    return 0;
}
