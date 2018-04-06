#include <iostream>
using namespace std;
#define maxSize 100
typedef struct BTNode
{
	char data;
	struct BTNode *lchild;
	struct BTNode *rchild;
}BTNode;


BTNode* newNode(char value)
{
	// Allocate memory for new node 
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));

	// Assign data to this node
	node->data = value;

	// Initialize left and right children as NULL
	node->lchild = NULL;
	node->rchild = NULL;
	return(node);
}

void visit(BTNode* node)
{
	printf("%c", node->data);// %c 输出字符型变量
}

void preorder(BTNode* p)
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

void levelorder(BTNode *p)
{
	int front, rear;
	BTNode *que[maxSize];
	front = rear = 0;
	BTNode*q;
	if (p != NULL)
	{
		rear = (rear + 1) % maxSize;
		que[rear] = p;
		while (front != rear)
		{
			front = (front + 1) % maxSize;
			q = que[front];
			visit(q);
			if (q->lchild != NULL)
			{
				rear = (rear + 1) % maxSize;
				que[rear] = q->lchild;
			}
			if (q->rchild != NULL)
			{
				rear = (rear + 1) % maxSize;
				que[rear] = q->rchild;
			}
		}
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

int main4()
{
	/*create root*/
	BTNode* root = newNode('A');
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
	preorder(root);		//先序遍历：ABDCEF
	printf("\n");
	inorder(root);		//中序遍历：DBAECF
	printf("\n");
	postorder(root);	//后序遍历：DBEFCA
	printf("\n");
	printf("%d", getDepth(root));//二叉树深度：3
	printf("\n");
	levelorder(root);	//层次遍历：ABCDEF
	system("pause");

	return 0;
}
