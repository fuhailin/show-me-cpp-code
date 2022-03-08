#include <iostream>
#include <string>
using namespace std;

class Solution {
 public:
  bool isNumber(string s) {
      
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<string> test = {"+100", "5e2", "-123", "3.1416", "-1E-16", "0123"};
  for (auto text : test) {
    cout << text << " : " << so.isNumber(text) << endl;
  }
  return 0;
}