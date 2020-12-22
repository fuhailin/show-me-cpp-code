/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      /Singly linked list in C++
=============================================================================*/
#include <iostream>

using namespace std;

// Struct inside the class LinkedList
// This is one node which is not needed by the caller. It is just
// for internal work.
// Definition for singly-linked list.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class LinkedList
{
  public:
    // constructor
    LinkedList()
    {
        head = NULL; // set head to NULL
        tail = NULL;
    }

    // destructor
    ~LinkedList()
    {
        ListNode *next = head;

        while (next)
        { // iterate over all elements
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
    ListNode *tail; //private member variable. It is just a pointer to the first & last Node
};