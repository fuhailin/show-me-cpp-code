#include "include/LinkedList.h"

class Solution {
public:
    ListNode *deleteMiddle(ListNode *head) {
        ListNode *hat = new ListNode(0);
        hat->next = head;
        ListNode *fast = head;
        ListNode *slow = hat;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode *tmp = slow->next;
        slow->next = tmp->next;
        delete tmp;
        return hat->next;
    }
};

int main(int argc, const char** argv) {
    Solution s;
    {
        std::vector<int> inputs = {1,3,4,7,1,2,6};
        ListNode* head = LinkedList::createLinkedList(inputs);
        ListNode* res = s.deleteMiddle(head);
        LinkedList::printLinkedList(res);
    }
    return 0;
}