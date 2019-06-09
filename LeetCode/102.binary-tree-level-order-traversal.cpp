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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> res;
        if (root == NULL)
            return res;
        queue<TreeNode *> Q;
        Q.push(root);
        while (!Q.empty())
        {
            int k = Q.size();
            vector<int> tmp;
            for (int j = 0; j < k; j++)
            {
                TreeNode *tr = Q.front();
                tmp.push_back(tr->val);
                if (tr->left)
                    Q.push(tr->left);
                if (tr->right)
                    Q.push(tr->right);
                Q.pop();
            }
            res.push_back(tmp);
        }
        return res;
    }
};
int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    vector<vector<int>> res = Solution().levelOrder(root);
    // cout << res << endl;
    return 0;
}