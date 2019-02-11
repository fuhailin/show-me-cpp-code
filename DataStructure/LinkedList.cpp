/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      /Singly linked list in C++
=============================================================================*/
#include "LinkedList.h"
#include <iostream>

using namespace std;

void LinkedList::addNode(int value)
{
    ListNode *temp = new ListNode(value); // create new Node
    if (head == NULL)
    {
        head = temp;
        tail = temp;
        temp = NULL;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}

void LinkedList::display()
{
    ListNode *temp; // = new ListNode;
    temp = head;
    while (temp)
    {
        cout << temp->val;
        if (temp->next)
            cout << "->";
        temp = temp->next;
    }
}

// returns the first element in the list and deletes the Node.
// caution, no error-checking here!
int LinkedList::popValue()
{
    ListNode *n = head;
    int ret = n->val;

    head = head->next;
    delete n;
    return ret;
}

int main0()
{
    LinkedList list;

    list.addNode(5);
    list.addNode(10);
    list.addNode(20);

    list.display();

    // cout << list.popValue() << endl;
    // cout << list.popValue() << endl;
    // cout << list.popValue() << endl;
    // because there is no error checking in popValue(), the following
    // is undefined behavior. Probably the program will crash, because
    // there are no more values in the list.
    // cout << list.popValue() << endl;
    return 0;
}