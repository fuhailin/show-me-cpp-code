#include <gtest/gtest.h>

#include <vector>

#include "include/ListNode.h"

class Solution {
   public:
    ListNode* reverseList(ListNode* head) {
        ListNode *cur = NULL, *pre = head;
        while (pre != NULL) {
            ListNode* t = pre->next;
            pre->next = cur;
            cur = pre;
            pre = t;
        }
        return cur;
    }
};

TEST(剑指offer, 反转链表) {
    Solution s;
    {
        std::vector<int> input = {1, 2, 3, 4, 5};
        ListNode* head = new ListNode(input[0]);
        ListNode* h = head;
        for (int i = 1; i < input.size(); ++i) {
            h->next = new ListNode(input[i]);
            h = h->next;
        }

        ListNode* exp = new ListNode(5, new ListNode(4, new ListNode(3, new ListNode(2, new ListNode(1)))));
        ListNode* ret = s.reverseList(head);

        ListNode* cur = ret;
        ListNode* cure = exp;
        while (cur != nullptr || cure != nullptr) {
            EXPECT_EQ(cur->val, cure->val);
            cur = cur->next;
            cure = cure->next;
        }
    }
}