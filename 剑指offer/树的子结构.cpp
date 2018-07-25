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

//创建二叉树结点
TreeNode *CreateBTNode(int value)
{
    // Allocate memory for new node
    TreeNode *node = new TreeNode(value);

    // Assign data to this node
    node->val = value;

    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    return (node);
}

bool HasSubtree(TreeNode *pRoot1, TreeNode *pRoot2)
{
    if(pRoot2==nullptr)
        return true;
    if(pRoot1==nullptr)
        return false;
}

int main()
{
    // 树中结点含有分叉，树B是树A的子结构
    //                  8                8
    //              /       \           / \
//             8         7         9   2
    //           /   \
//          9     2
    //               / \
//              4   7

    TreeNode *rootA = CreateBTNode(8);

    rootA->left = CreateBTNode(8);
    rootA->right = CreateBTNode(7);

    rootA->left->left = CreateBTNode(9);
    rootA->left->right = CreateBTNode(2);

    rootA->left->right->left = CreateBTNode(4);
    rootA->left->right->right = CreateBTNode(7);

    TreeNode *rootB = CreateBTNode(8);
    rootB->left = CreateBTNode(9);
    rootB->right = CreateBTNode(2);

    if (HasSubtree(rootA, rootB))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}