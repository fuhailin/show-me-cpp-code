#include <gtest/gtest.h>

#include "include/LinkedList.h"

class Solution {
   public:
        * reverseKGroup(ListNode* head, int k) {
        ListNode *hair = new ListNode(0), *pre = hair;
        hair->next = head;
        while (head) {
            ListNode *tail = pre;
            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    return hair->next;
                }
            }
            ListNode *nex = tail->next;
            // 这里是 C++17 的写法，也可以写成
            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
            // head = result.first;
            // tail = result.second;
            tie(head, tail) = reverseList(head, tail);
            // 把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }
        return hair->next;
    }

    std::pair<ListNode*, ListNode*> reverseList(ListNode* head, ListNode* tail) {
        ListNode *cur = head, *pre = NULL, *next = NULL;
        while (cur != tail) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return {tail, head};
    }
};

TEST(剑指offer, K个一组翻转链表) {
    Solution s;
    {
        std::vector<int> inputs = {1, 2, 3, 4, 5};
        ListNode* head = LinkedList::createLinkedList(inputs);

        ListNode* exp = new ListNode(2, new ListNode(1, new ListNode(4, new ListNode(3, new ListNode(5)))));
        ListNode* ret = s.reverseKGroup(head, 2);

        LinkedList::printLinkedList(ret);

        // ListNode* cur = ret;
        // ListNode* cure = exp;
        // while (cur != nullptr || cure != nullptr) {
        //     EXPECT_EQ(cur->val, cure->val);
        //     cur = cur->next;
        //     cure = cure->next;
        // }
    }
}