#include <string>
#include <vector>
using namespace std;

class Trie {
  bool isEnd;
  vector<Trie*> next;

 public:
  Trie() : next(26), isEnd(false) {}

  void insert(string word) {
    Trie* node = this;
    for (char ch : word) {
      ch -= 'a';
      if (node->next[ch] == nullptr) {
        node->next[ch] = new Trie();
      }
      node = node->next[ch];
    }
    node->isEnd = true;
  }

  bool search(string word) {
    Trie* node = this;
    for (char ch : word) {
      ch -= 'a';
      if (node->next[ch] == nullptr) {
        return false;
      }
      node = node->next[ch];
    }
    return node->isEnd;
  }

  bool startsWith(string prefix) {
    Trie* node = this;
    for (char ch : prefix) {
      ch -= 'a';
      if (node->next[ch] == nullptr) {
        return false;
      }
      node = node->next[ch];
    }
    return true;
  }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */