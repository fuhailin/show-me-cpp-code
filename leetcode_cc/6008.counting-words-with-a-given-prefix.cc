#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
  bool prefix(string word, string pref) {
    int i = 0;
    while (i < word.size() && i < pref.size()) {
      if (word[i] != pref[i]) {
        return false;
      }
      i++;
    }
    if (i == pref.size()) {
      return true;
    } else {
      return false;
    }
  }

 public:
  int prefixCount(vector<string>& words, string pref) {
    int res = 0;
    for (string& word : words) {
      if (prefix(word, pref)) {
        res++;
      }
    }
    return res;
  }
};

int main(int argc, const char** argv) {
  Solution so;
  vector<string> test = {"pay", "attention", "practice", "attend"};
  //   vector<string> test = {
  //       "kttxeksggb", "vucqwew",    "lyknscc",  "mryl",       "vwarnwkfmd",
  //       "ivawxbntgs", "mylw",       "namybmfy", "uosag",      "rzernqxyn",
  //       "puf",        "hfwjnmvm",   "jjfyd",    "xteybd",     "v",
  //       "ywntwzn",    "npsogop",    "brgvlw",   "vewhi",      "brk",
  //       "hheub",      "zl",         "vt",       "bxjtjivep",  "p",
  //       "io",         "xotulskjmt", "mctffonh", "pmeuqhoe",   "ghktrtq",
  //       "u",          "ngnvwan",    "pqmlvvhl", "enjf",       "qomcejb",
  //       "twgqww",     "bnilyqy",    "nc",       "fttlodnz",   "fya",
  //       "g",          "uoivsr",     "gtxgcaf",  "qs",         "gkfl",
  //       "sdmacxf",    "mzy",        "xjv",      "yipc",       "rctqugjjk",
  //       "myij",       "xxg",        "vyup",     "utqxplpsa",  "imbteaczlc",
  //       "qfgdcz",     "atfn",       "pxcsg",    "f",          "omukbiaudb",
  //       "uh",         "uobwgt",     "hgqipk",   "zunfzinenk", "i",
  //       "p",          "pet",        "fxai",     "ortqpwkukg", "rxgh",
  //       "ylfh"};
  //   string pref = "ikwjoty";
  string pref = "at";

  int res = so.prefixCount(test, pref);
  cout << res << endl;

  return 0;
}