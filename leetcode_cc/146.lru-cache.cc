#include <gtest/gtest.h>

#include <unordered_map>

using namespace std;

struct DLinkedNode {
  int key, value;
  DLinkedNode* prev;
  DLinkedNode* next;
  DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
  DLinkedNode(int _key, int _value)
      : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
 private:
  unordered_map<int, DLinkedNode*> cache;
  DLinkedNode* head;
  DLinkedNode* tail;
  int size;
  int capacity;

 public:
  LRUCache(int _capacity) : capacity(_capacity), size(0) {
    // 使用伪头部和伪尾部节点
    head = new DLinkedNode();
    tail = new DLinkedNode();
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (!cache.count(key)) {
      return -1;
    }
    // 如果 key 存在，先通过哈希表定位，再移到头部
    DLinkedNode* node = cache[key];
    moveToHead(node);
    return node->value;
  }

  void put(int key, int value) {
    if (!cache.count(key)) {
      // 如果 key 不存在，创建一个新的节点
      DLinkedNode* node = new DLinkedNode(key, value);
      // 添加进哈希表
      cache[key] = node;
      // 添加至双向链表的头部
      addToHead(node);
      ++size;
      if (size > capacity) {
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
};

TEST(leetcode, LRU缓存机制) {
  LRUCache* obj = new LRUCache(2);
  obj->put(1, 1);  // 缓存是 {1=1}
  obj->put(2, 2);  // 缓存是 {1=1, 2=2}
  obj->get(1);     // 返回 1
  obj->put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  obj->get(2);     // 返回 -1 (未找到)
  obj->put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  obj->get(1);     // 返回 -1 (未找到)
  obj->get(3);     // 返回 3
  obj->get(4);     // 返回 4
}