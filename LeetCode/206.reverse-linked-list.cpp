#include <iostream>

using namespace std;
/**
 * Definition for singly-linked list.
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
  public:
    ListNode *reverseList_Recursive(ListNode *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        ListNode *p = reverseList_Recursive(head->next);
        head->next->next = head;
        head->next = NULL;
        return p;
    }

    ListNode *reverseList_Iterative(ListNode *head)
    {
        ListNode *cur = head;
        ListNode *pre = NULL;
        while(cur!=NULL){
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}
