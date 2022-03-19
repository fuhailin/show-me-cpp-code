#include "cache.h"

#include "bits/stdc++.h"

TEST(Cache, LRU_Cache) {
  Cache<int, int>* lRUCache = new LRUCache<int, int>(2);
  lRUCache->put(1, 1);             // 缓存是 {1=1}
  lRUCache->put(2, 2);             // 缓存是 {1=1, 2=2}
  EXPECT_EQ(1, lRUCache->get(1));  // 返回 1
  lRUCache->put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  EXPECT_EQ(-1, lRUCache->get(2));  // 返回 -1 (未找到)
  lRUCache->put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  EXPECT_EQ(-1, lRUCache->get(1));  // 返回 -1 (未找到)
  EXPECT_EQ(3, lRUCache->get(3));   // 返回 3
  EXPECT_EQ(4, lRUCache->get(4));   // 返回 4
}

TEST(Cache, LFU_Cache) {
  // LFUCache<int, int>* obj = new LFUCache<int, int>(2);
  // int param_1 = obj->get(1);
  // obj->put(1, 1);
  // obj->put(2, 2);
  // int param_2 = obj->get(1);
  Cache<int, int>* lfu = new LFUCache<int, int>(2);
  lfu->put(1, 1);             // cache=[1,_], cnt(1)=1
  lfu->put(2, 2);             // cache=[2,1], cnt(2)=1, cnt(1)=1
  EXPECT_EQ(1, lfu->get(1));  // 返回 1
                              // cache=[1,2], cnt(2)=1, cnt(1)=2
  lfu->put(3, 3);  // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
                   // cache=[3,1], cnt(3)=1, cnt(1)=2
  EXPECT_EQ(-1, lfu->get(2));  // 返回 -1（未找到）
  EXPECT_EQ(3, lfu->get(3));   // 返回 3
                               // cache=[3,1], cnt(3)=2, cnt(1)=2
  lfu->put(4, 4);  // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
                   // cache=[4,3], cnt(4)=1, cnt(3)=2
  EXPECT_EQ(-1, lfu->get(1));  // 返回 -1（未找到）
  EXPECT_EQ(3, lfu->get(3));   // 返回 3
                               // cache=[3,4], cnt(4)=1, cnt(3)=3
  EXPECT_EQ(4, lfu->get(4));   // 返回 4
                               // cache=[3,4], cnt(4)=2, cnt(3)=3
}
