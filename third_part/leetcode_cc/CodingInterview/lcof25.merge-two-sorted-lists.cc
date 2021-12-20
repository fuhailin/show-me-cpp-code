#include <gtest/gtest.h>

#include "include/LinkedList.h"

class Solution {
   public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* hair = new ListNode(0);
        ListNode* cur = hair;
        while (l1 && l2) {
            if (l1->val >= l2->val) {
                cur->next = l2;
                l2 = l2->next;
            } else {
                cur->next = l1;
                l1 = l1->next;
            }
            cur = cur->next;
        }
        if (!l1) {
            cur->next = l2;
        } else {
            cur->next = l1;
        }
        return hair->next;
    }
};