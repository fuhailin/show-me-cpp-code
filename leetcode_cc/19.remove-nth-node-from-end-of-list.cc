#include <gtest/gtest.h>

#include "include/LinkedList.h"

class Solution {
   public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* hat = new ListNode(0);
        hat->next = head;
        ListNode *fast = head, *slow = hat;
        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        ListNode* tmp = slow->next;
        slow->next = tmp->next;
        delete tmp, hat;
        return hat->next;
    }
};