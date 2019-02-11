#include <iostream>
#include <queue>
using namespace std;
#define maxSize 100
struct BTNode
{
	char data;
	BTNode *lchild;
	BTNode *rchild;
	BTNode(char x) : data(x), lchild(NULL), rchild(NULL) {}
};

BTNode *newNode(char value)
{
	// Allocate memory for new node
	BTNode *node = new BTNode(value);
	// Assign data to this node
	// Initialize left and right children as NULL
	return (node);
}

void visit(BTNode *node)
{
	cout << node->data; // %c 输出字符型变量
}

void preorder(BTNode *p)
{
	if (p != NULL)
	{
		visit(p);
		preorder(p->lchild);
		preorder(p->rchild);
	}
}

void inorder(BTNode *p)
{
	if (p != NULL)
	{
		inorder(p->lchild);
		visit(p);
		inorder(p->rchild);
	}
}

void postorder(BTNode *p)
{
	if (p != NULL)
	{
		postorder(p->lchild);
		postorder(p->rchild);
		visit(p);
	}
}


// Iterative method to find height of Bianry Tree
void levelorder(BTNode *root)
{
	// Base Case
	if (root == NULL)
		return;

	// Create an empty queue for level order tarversal
	queue<BTNode *> q;

	// Enqueue Root and initialize height
	q.push(root);

	while (q.empty() == false)
	{
		// Print front of queue and remove it from queue
		BTNode *node = q.front();
		visit(node);
		// cout << node->data << " ";
		q.pop();

		/* Enqueue left child */
		if (node->lchild != NULL)
			q.push(node->lchild);

		/*Enqueue right child */
		if (node->rchild != NULL)
			q.push(node->rchild);
	}
}

int getDepth(BTNode *p)
{
	int LD, RD;
	if (p == NULL)
		return 0;
	else
	{
		LD = getDepth(p->lchild);
		RD = getDepth(p->rchild);
		return (LD > RD ? LD : RD) + 1;
	}
}

int main()
{
	/*create root*/
	BTNode *root = newNode('A');
	/* following is the tree after above statement

	A
	/   \
	NULL  NULL
	*/

	root->lchild = newNode('B');
	root->rchild = newNode('C');
	/* 2 and 3 become left and right children of 1
	A
	/   \
	B      C
	/    \    /  \
	NULL NULL NULL NULL
	*/

	root->lchild->lchild = newNode('D');
	root->rchild->lchild = newNode('E');
	root->rchild->rchild = newNode('F');
	/* 4 becomes left child of 2
	A
	/			\
	B				C
	/   \		/		\
	D  NULL		E		  F
	/ \			/ \		 / \
	NULL NULL NULL NULL NULL NULL
	*/

	//getchar();
	preorder(root); //先序遍历：ABDCEF
	cout << endl;
	inorder(root); //中序遍历：DBAECF
	cout << endl;
	postorder(root); //后序遍历：DBEFCA
	cout << endl;
	cout << getDepth(root) << endl; //二叉树深度：3
	levelorder(root);				//层次遍历：ABCDEF
	return 0;
}
