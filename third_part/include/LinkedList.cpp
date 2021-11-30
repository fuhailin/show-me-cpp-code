/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      /Singly linked list in C++
=============================================================================*/
#include "include/LinkedList.h"

#include <iostream>

void printLinkedList(ListNode *head) {
    ListNode *temp = head;
    while (temp) {
        std::cout << temp->val;
        if (temp->next)
            std::cout << "->";
        temp = temp->next;
    }
}

ListNode *createLinkedList(std::vector<int> nodes) {
    ListNode *hair = new ListNode(0);
    ListNode *cur = hair;
    for (auto x : nodes) {
        cur->next = new ListNode(x);
        cur = cur->next;
    }
    return hair->next;
}

void myLinkedList::addNode(int value) {
    ListNode *temp = new ListNode(value);  // create new Node
    if (head == NULL) {
        head = temp;
        tail = temp;
        temp = NULL;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void myLinkedList::display() {
    ListNode *temp;  // = new ListNode;
    temp = head;
    while (temp) {
        std::cout << temp->val;
        if (temp->next)
            std::cout << "->";
        temp = temp->next;
    }
}

// returns the first element in the list and deletes the Node.
// caution, no error-checking here!
int myLinkedList::popValue() {
    ListNode *n = head;
    int ret = n->val;

    head = head->next;
    delete n;
    return ret;
}

int main() {
    myLinkedList list;

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