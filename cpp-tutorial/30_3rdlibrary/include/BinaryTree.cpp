/*=============================================================================
#  Author:           Hailin - https://fuhailin.github.io/
#  Email:            hailinfufu@outlook.com
#  Description:      二叉树的前、中、后序遍历的递归与非递归写法，层次遍历/
=============================================================================*/
#include <iostream>
#include <stack>
#include <queue>
#include "BinaryTree.h"
using namespace std;

void BinaryTree::preorder_Recursive(BTNode *root)
{
    if (root != NULL)
    {
        visit(root);
        preorder_Recursive(root->lchild);
        preorder_Recursive(root->rchild);
    }
}

void BinaryTree::inorder_Recursive(BTNode *root)
{
    if (root != NULL)
    {
        inorder_Recursive(root->lchild);
        visit(root);
        inorder_Recursive(root->rchild);
    }
}

void BinaryTree::postorder_Recursive(BTNode *root)
{
    if (root != NULL)
    {
        postorder_Recursive(root->lchild);
        postorder_Recursive(root->rchild);
        visit(root);
    }
}

void BinaryTree::preorder_Iterative(BTNode *root)
{
    stack<BTNode *> s;
    s.push(root);
    while (!s.empty())
    {
        BTNode *node = s.top();
        s.pop();
        visit(node);
        if (node->rchild != NULL)
            s.push(node->rchild);
        if (node->lchild != NULL)
            s.push(node->lchild);
    }
}

void BinaryTree::inorder_Iterative(BTNode *root)
{
    stack<BTNode *> s;
    BTNode *p = root;
    while (p != NULL || !s.empty())
    {
        while (p != NULL)
        {
            s.push(p);
            p = p->lchild;
        }
        if (!s.empty())
        {
            p = s.top();
            visit(p);
            s.pop();
            p = p->rchild;
        }
    }
}

void BinaryTree::postorder_Iterative(BTNode *root)
{
    stack<BTNode *> s1, s2;
    s1.push(root);
    while (!s1.empty())
    {
        BTNode *node = s1.top();
        s2.push(node);
        s1.pop();
        if (node->lchild)
            s1.push(node->lchild);
        if (node->rchild)
            s1.push(node->rchild);
    }
    while (!s2.empty())
    {
        BTNode *node = s2.top();
        visit(node);
        s2.pop();
    }
}
void BinaryTree::levelorder(BTNode *root)
{
    queue<BTNode *> q;
    q.push(root);
    while (!q.empty())
    {
        root = q.front();
        visit(root);
        q.pop();
        if (root->lchild)
            q.push(root->lchild);
        if (root->rchild)
            q.push(root->rchild);
    }
}
int BinaryTree::getDepth(BTNode *root)
{
    if (root == NULL)
        return 0;
    else
        return max(getDepth(root->lchild), getDepth(root->rchild)) + 1;
}

BTNode *BinaryTree::newNode(char value)
{
    // Allocate memory for new node
    BTNode *node = new BTNode(value);
    // Assign data to this node
    // Initialize left and right children as NULL
    return (node);
}
void BinaryTree::visit(BTNode *node)
{
    cout << node->data;
}

int main1(int argc, char const *argv[])
{
    /*create root*/
    BinaryTree btree;
    BTNode *root = btree.newNode('A');
    /* following is the tree after above statement

	A
	/   \
	NULL  NULL
	*/

    root->lchild = btree.newNode('B');
    root->rchild = btree.newNode('C');
    /* 2 and 3 become left and right children of 1
	A
	/   \
	B      C
	/    \    /  \
	NULL NULL NULL NULL
	*/

    root->lchild->lchild = btree.newNode('D');
    root->rchild->lchild = btree.newNode('E');
    root->rchild->rchild = btree.newNode('F');
    /* 4 becomes left child of 2
	A
	/			\
	B				C
	/   \		/		\
	D  NULL		E		  F
	/ \			/ \		 / \
	NULL NULL NULL NULL NULL NULL
	*/
    cout << "preorder_Iterative:";
    btree.preorder_Iterative(root); //先序遍历：ABDCEF
    cout << "\npreorder_Recursive:";
    btree.preorder_Recursive(root); //先序遍历：ABDCEF
    cout << "\ninorder_Recursive:";
    btree.inorder_Recursive(root); //中序遍历：DBAECF
    cout << "\ninorder_Iterative:";
    btree.inorder_Iterative(root); //中序遍历：DBAECF
    cout << "\npostorder_Recursive:";
    btree.postorder_Recursive(root); //后序遍历：DBEFCA
    cout << "\npostorder_Iterative:";
    btree.postorder_Iterative(root);
    cout << "\nTree Depth:";
    cout << btree.getDepth(root); //二叉树深度：3
    cout << "\nlevelorer:";
    btree.levelorder(root); //层次遍历：ABCDEF
    return 0;
}