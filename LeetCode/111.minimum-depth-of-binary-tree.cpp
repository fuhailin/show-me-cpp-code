#include <iostream>
#include <queue>
using namespace std;

//Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        if (root->left == NULL)
            return 1 + minDepth(root->right);
        else if (root->right == NULL)
            return 1 + minDepth(root->left);
        else return 1 + min(minDepth(root->left), minDepth(root->right));
    }

    int minDepth_BFS(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        queue<TreeNode *> Q;
        Q.push(root);
        int i = 0;
        while (!Q.empty())
        {
            ++i;
            int k = Q.size();
            for (int j = 0; j < k; j++)
            {
                TreeNode *tr = Q.front();
                if (tr->left == NULL && tr->right == NULL)
                    return i;
                if (tr->left)
                    Q.push(tr->left);
                if (tr->right)
                    Q.push(tr->right);
                Q.pop();
            }
        }
    }
};
int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    int res = Solution().minDepth_BFS(root);
    cout << res << endl;
    return 0;
}