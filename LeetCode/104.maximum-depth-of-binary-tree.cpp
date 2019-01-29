#include <iostream>

using namespace std;
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
    int maxDepth(TreeNode *root)
    {
        if (root == NULL)
            return 0;

        else if (root->left == NULL && root->right == NULL)
        {
            return 1;
        }

        return max(maxDepth(root->left), maxDepth(root->right));
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}