#include <gtest/gtest.h>

#include <vector>

#include "include/LinkedList.h"

class Solution {
   public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        if (head == NULL || k == 0) {
            return NULL;
        }
        ListNode* fast = head;
        ListNode* slow = head;
        int step = 0;
        while (fast) {
            fast = fast->next;
            step++;
            if (step > k) {
                slow = slow->next;
            }
        }
        if (step < k) {
            return NULL;
        }
        return slow;
    }
};