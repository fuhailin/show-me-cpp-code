#include <gtest/gtest.h>


struct DLinkedNode {
    int key, value;
    DLinkedNode *prev;
    DLinkedNode *next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
   public:
    LRUCache(int capacity) {
        private 
    }

    int get(int key) {
    }

    void put(int key, int value) {
    }
};

TEST(leetcode, LRU 缓存机制) {
    *LRUCache* obj = new LRUCache(capacity);
    auto keys = [ "LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get" ];
    auto values = [ [2], [ 1, 1 ], [ 2, 2 ], [1], [ 3, 3 ], [2], [ 4, 4 ], [1], [3], [4] ];

    *int param_1 = obj->get(key);
    *obj->put(key, value);
}