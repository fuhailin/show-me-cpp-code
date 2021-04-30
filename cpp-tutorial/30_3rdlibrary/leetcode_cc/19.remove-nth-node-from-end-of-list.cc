#include <gtest/gtest.h>

#include "include/LinkedList.h"

class Solution {
   public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *fast = head, *slow = head;
        int step = 0;
        while (fast) {
            if (step <= n) {
                fast = fast->next;
            } else {
                fast = fast->next;
                slow = slow->next;
            }
            ++step;
        }
        if (step < n) {
            return nullptr;
        }
        if (step == n) {
            return head->next;
        } else {
            slow->next = slow->next->next;
            return head;
        }
    }
};