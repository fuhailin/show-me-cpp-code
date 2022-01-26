/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      /Singly linked list in C++
=============================================================================*/
#include <iostream>
#include <vector>

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

namespace LinkedList {
void printLinkedList(ListNode *head);

ListNode *createLinkedList(std::vector<int> nodes);
} // namespace LinkedList

class myLinkedList {
public:
  // constructor
  myLinkedList() {
    head = NULL; // set head to NULL
    tail = NULL;
  }

  // destructor
  ~myLinkedList() {
    ListNode *next = head;

    while (next) { // iterate over all elements
      ListNode *deleteMe = next;
      next = next->next; // save pointer to the next element
      delete deleteMe;   // delete the current entry
    }
  }

  void addNode(int value);

  void display();

  // returns the first element in the list and deletes the Node.
  // caution, no error-checking here!
  int popValue();
  ListNode *head;

private:
  ListNode *tail; // private member variable. It is just a pointer to the first
                  // & last Node
};