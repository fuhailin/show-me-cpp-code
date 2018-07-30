#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL)
    {
    }
};


void Mirror(TreeNode *pRoot)
{
    if(pRoot==NULL)
        return;
    Mirror(pRoot->left);
    Mirror(pRoot->right);
    TreeNode *tmp;
    tmp=pRoot->left;
    pRoot->left=pRoot->right;
    pRoot->right=tmp;
}

int main()
{
// 二叉树的镜像定义：源二叉树 
//     	    8
//     	   /  \
//     	  6   10
//     	 / \  / \
//     	5  7 9 11
//     	镜像二叉树
//     	    8
//     	   /  \
//     	  10   6
//     	 / \  / \
//     	11 9 7  5
    TreeNode *rootA=TreeNode(8);


}
