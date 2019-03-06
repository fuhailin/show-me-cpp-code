#include <iostream>
#include <vector>
#include <queue>

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
vector<int> PrintFromTopToBottom(TreeNode *root)
{
      vector<int> v;
    if (root == NULL)
        return v;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode *tmp = q.front();
        q.pop();
        if (!tmp == NULL)
        {
            v.push_back(tmp->val);
            q.push(tmp->left);
            q.push(tmp->right);
        }
    }
    return v;
}
int main()
{
    return 0;
}