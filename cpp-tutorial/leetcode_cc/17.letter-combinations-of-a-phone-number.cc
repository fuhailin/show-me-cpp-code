#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   private:
    unordered_map<char, string> phoneMap{
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}};
    

    vector<string> result;
    string combination;
    void backtracking(const string& digits, int index) {
        if (index == digits.size()) {
            result.emplace_back(combination);
            return;
        }
        char digit = digits[index];
        const string& letters = phoneMap.at(digit);
        for (const char& letter : letters) {
            combination.push_back(letter);
            backtracking(digits, index + 1);
            combination.pop_back();
        }
    }

   public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return result;
        }
        backtracking(digits, 0);
        return result;
    }
};