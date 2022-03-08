#ifndef CACHE_H_
#define CACHE_H_
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <thread>
#include <unordered_map>

using namespace std;

template <class K, class V>
class Cache {
 public:
  Cache() {}
  Cache(size_t _capacity) { capacity = _capacity; }
  virtual V get(K key) = 0;
  virtual void put(const K key, V value) = 0;

 protected:
  size_t capacity;
};

template <class K, class V>
class LRUCache : public Cache<K, V> {
 private:
  struct DLinkedNode {
    K key;
    V value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(K _key, V _value)
        : key(_key), value(_value), prev(nullptr), next(nullptr) {}
  };
  DLinkedNode *head, *tail;
  std::map<K, DLinkedNode*> cache;
  size_t size;

  void addToHead(DLinkedNode* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }

  void removeNode(DLinkedNode* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void moveToHead(DLinkedNode* node) {
    removeNode(node);
    addToHead(node);
  }

  DLinkedNode* removeTail() {
    DLinkedNode* node = tail->prev;
    removeNode(node);
    return node;
  }

 public:
  LRUCache(size_t _capacity) {
    Cache<K, V>::capacity = _capacity;
    size = 0;
    cache.clear();
    head = new DLinkedNode();
    tail = new DLinkedNode();
    head->next = tail;
    tail->prev = head;
  }

  V get(K key) {
    if (!cache.count(key)) {
      return -1;
    }
    // 如果 key 存在，先通过哈希表定位，再移到头部
    DLinkedNode* node = cache[key];
    moveToHead(node);
    return node->value;
  }

  void put(K key, V value) {
    if (!cache.count(key)) {
      // 如果 key 不存在，创建一个新的节点
      DLinkedNode* node = new DLinkedNode(key, value);
      // 添加进哈希表
      cache[key] = node;
      // 添加至双向链表的头部
      addToHead(node);
      ++size;
      if (size > Cache<K, V>::capacity) {
        // 如果超出容量，删除双向链表的尾部节点
        DLinkedNode* removed = removeTail();
        // 删除哈希表中对应的项
        cache.erase(removed->key);
        // 防止内存泄漏
        delete removed;
        --size;
      }
    } else {
      // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
      DLinkedNode* node = cache[key];
      node->value = value;
      moveToHead(node);
    }
  }
};

template <class K, class V>
class LFUCache : public Cache<K, V> {
 private:
  struct Node {
    int freq;
    K key;
    V val;
    Node* prev;
    Node* next;

    Node() : key(-1), val(-1), freq(0), prev(nullptr), next(nullptr) {}

    Node(K _key, V _value)
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

  size_t min_freq;
  size_t max_freq;
  std::unordered_map<K, Node*> occ;
  std::unordered_map<K, FreqList*> freq_table;
  mutex mu_;

  bool empty(FreqList* list) {
    return list->vhead->next == list->vtail ? true : false;
  }

  void deleteNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void addHead(Node* node) {
    int freq = node->freq;
    if (freq_table.find(freq) == freq_table.end()) {
      freq_table[freq] = new FreqList(freq);
    }
    FreqList* list = freq_table[freq];
    node->next = list->vhead->next;
    list->vhead->next->prev = node;
    node->prev = list->vhead;
    list->vhead->next = node;
  }

  void popTail() {
    Node* node = freq_table[min_freq]->vtail->prev;
    deleteNode(node);
    occ.erase(node->key);
  }

 public:
  LFUCache(size_t _capacity) {
    Cache<K, V>::capacity = _capacity;
    min_freq = 0;
    max_freq = 0;
    occ.clear();
    freq_table.clear();
  }

  size_t size() {
    std::unique_lock<std::mutex> l(mu_);
    return occ.size();
  }

  int get(int key) {
    int res = -1;
    auto it = occ.find(key);
    if (it != occ.end()) {
      Node* node = it->second;
      res = node->val;
      deleteNode(node);
      node->freq++;
      if (empty(freq_table[min_freq])) min_freq++;
      addHead(node);
    }
    return res;
  }

  void put(int key, int value) {
    if (Cache<K, V>::capacity == 0) return;
    if (get(key) != -1) {
      occ[key]->val = value;
    } else {
      if (occ.size() == Cache<K, V>::capacity) {
        popTail();
      }
      Node* node = new Node(key, value);
      occ[key] = node;
      min_freq = 1;  //新插入的 频率一定最少, 为1
      addHead(node);
    }
  }
};

#endif  // CACHE_H_
