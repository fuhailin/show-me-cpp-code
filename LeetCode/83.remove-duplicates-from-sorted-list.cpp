#include <iostream>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *deleteDuplicates(ListNode *head)
{
    ListNode *p = head;
    while (p != NULL && p->next != NULL)
    {
        if (p->val == p->next->val)
        {
            p->next = p->next->next;
        }
        else
        {
            p = p->next;
        }
    }
    return head;
}

int main(int argc, char const *argv[])
{

    return 0;
}