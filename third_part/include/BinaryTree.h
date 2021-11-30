/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      /Singly linked list in C++
=============================================================================*/
#include <iostream>

using namespace std;

// Struct inside the class BinaryTree
// This is one node which is not needed by the caller. It is just
// for internal work.
// Definition for singly-linked list.
struct BTNode
{
    char data;
    BTNode *lchild;
    BTNode *rchild;
    BTNode(char x) : data(x), lchild(NULL), rchild(NULL) {}
};
class BinaryTree
{
  public:
    // constructor
    // BinaryTree()
    // {
    //     root = NULL; // set root to NULL
    // }

    // destructor
    // ~BinaryTree()
    // {
    //     BTNode *node = root;

    //     if (node == nullptr)
    //     {
    //         return;
    //     }
    //     ~BinaryTree(node->lchild);
    //     ~BinaryTree(node->rchild);
    //     delete node;
    // }
    void preorder_Recursive(BTNode *root);
    void preorder_Iterative(BTNode *root);
    void inorder_Recursive(BTNode *root);
    void inorder_Iterative(BTNode *root);
    void postorder_Recursive(BTNode *root);
    void postorder_Iterative(BTNode *root);
    void levelorder(BTNode *root);

    BTNode *newNode(char value);
    

    int getDepth(BTNode *root);

    void visit(BTNode *node);

    BTNode *root;
};