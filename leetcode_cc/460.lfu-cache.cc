#include <map>
#include <set>
#include <unordered_map>
using namespace std;

struct Node {
  int key, val, freq;
  Node* prev;
  Node* next;

  Node() : key(-1), val(-1), freq(0), prev(nullptr), next(nullptr) {}

  Node(int _key, int _value)
      : key(_key), val(_value), freq(1), prev(nullptr), next(nullptr) {}
};

struct FreqList {
  int freq;
  Node* vhead;
  Node* vtail;

  FreqList(int _freq) : freq(_freq), vhead(new Node()), vtail(new Node()) {
    vhead->next = vtail;
    vtail->prev = vhead;
  }
};

class LFUCache {
 private:
  unordered_map<int, Node*> occ;
  unordered_map<int, FreqList*> freq_map;
  int capacity, min_freq;

 public:
  LFUCache(int capacity) : capacity(capacity) {}

  bool empty(FreqList* list) {
    return list->vhead->next == list->vtail ? true : false;
  }

  void deleteNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void addHead(Node* node) {
    int freq = node->freq;
    if (freq_map.find(freq) == freq_map.end()) {
      freq_map[freq] = new FreqList(freq);
    }
    FreqList* list = freq_map[freq];
    node->next = list->vhead->next;
    list->vhead->next->prev = node;
    node->prev = list->vhead;
    list->vhead->next = node;
  }

  void popTail() {
    Node* node = freq_map[min_freq]->vtail->prev;
    deleteNode(node);
    occ.erase(node->key);
  }

  int get(int key) {
    int res = -1;
    auto it = occ.find(key);
    if (it != occ.end()) {
      Node* node = it->second;
      res = node->val;
      deleteNode(node);
      node->freq++;
      if (empty(freq_map[min_freq])) min_freq++;
      addHead(node);
    }
    return res;
  }

  void put(int key, int value) {
    if (capacity == 0) return;
    if (get(key) != -1) {
      occ[key]->val = value;
    } else {
      if (occ.size() == capacity) {
        popTail();
      }
      Node* node = new Node(key, value);
      occ[key] = node;
      min_freq = 1;  //新插入的 频率一定最少, 为1
      addHead(node);
    }
  }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/**
 * Your LFUCache object will be instantiated and called as such:

 */

int main(int argc, const char** argv) {
  LFUCache* obj = new LFUCache(2);
  int param_1 = obj->get(1);
  obj->put(1, 1);
  obj->put(2, 2);
  int param_2 = obj->get(1);
  return 0;
}