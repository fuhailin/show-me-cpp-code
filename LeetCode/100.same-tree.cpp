#include <iostream>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (p == NULL || q == NULL)
        return (p == q);
    return (isSameTree(p->left, q->left) && isSameTree(p->right, q->right) && (p->val == q->val));
}
int main(int argc, char const *argv[])
{

    return 0;
}