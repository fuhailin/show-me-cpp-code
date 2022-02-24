#include "../DataStructure/LinkedList.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
  public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.empty())
            return NULL;
        ListNode *result = lists[0];
        for (int i = 1; i < lists.size(); i++)
        {
            result = mergeTwoLists_iterative(result, lists[i]);
        }
        return result;
    }

    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        int size = lists.size();
        ListNode *head = NULL;
        vector<int> numbers;

        for (auto curList : lists)
        {
            while (curList != NULL)
            {
                numbers.push_back(curList->val);
                curList = curList->next;
            }
        }
        sort(numbers.begin(), numbers.end());
        head = AddNumbers(numbers);
        return head;
    }

  private:
    ListNode *AddNumbers(vector<int> numbers)
    {
        if (numbers.size() == NULL)
            return NULL;
        ListNode *head = NULL;
        ListNode *tmp;
        for (auto it : numbers)
        {
            if (head == NULL)
            {
                head = new ListNode(it);
                tmp = head;
            }
            else
            {
                tmp->next = new ListNode(it);
                tmp = tmp->next;
            }
        }
        return head;
    }

    ListNode *mergeTwoLists_recursive(ListNode *l1, ListNode *l2)
    {
        if (l1 == NULL)
            return l2;
        if (l2 == NULL)
            return l1;
        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists_recursive(l1->next, l2);
            return l1;
        }
        else
        {
            l2->next = mergeTwoLists_recursive(l1, l2->next);
            return l2;
        }
    }

    ListNode *mergeTwoLists_iterative(ListNode *l1, ListNode *l2)
    {
        ListNode dummy(-1);
        ListNode *tail = &dummy;
        while (l1 != NULL && l2 != NULL)
        {
            if (l1->val < l2->val)
            {
                tail->next = l1;
                l1 = l1->next;
            }
            else
            {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 == NULL ? l2 : l1;
        return dummy.next;
    }
};

int main(int argc, char const *argv[])
{
    vector<ListNode *> test;

    LinkedList list1;
    list1.addNode(1);
    list1.addNode(4);
    list1.addNode(5);
    test.push_back(list1.head);

    LinkedList list2;
    list2.addNode(1);
    list2.addNode(3);
    list2.addNode(4);
    test.push_back(list2.head);

    LinkedList list3;
    list3.addNode(2);
    list3.addNode(6);
    test.push_back(list3.head);

    LinkedList res;

    res.head = Solution().mergeKLists(test);
    res.display();

    return 0;
}