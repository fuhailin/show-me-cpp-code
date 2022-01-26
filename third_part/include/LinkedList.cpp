/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      /Singly linked list in C++
=============================================================================*/
#include "LinkedList.h"

#include <iostream>

void LinkedList::printLinkedList(ListNode *head) {
  ListNode *temp = head;
  while (temp) {
    std::cout << temp->val;
    if (temp->next)
      std::cout << "->";
    temp = temp->next;
  }
}

ListNode *LinkedList::createLinkedList(std::vector<int> nodes) {
  ListNode *hair = new ListNode(0);
  ListNode *cur = hair;
  for (auto x : nodes) {
    cur->next = new ListNode(x);
    cur = cur->next;
  }
  return hair->next;
}

void myLinkedList::addNode(int value) {
  ListNode *temp = new ListNode(value); // create new Node
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
  ListNode *temp; // = new ListNode;
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