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
        return max(1 + maxDepth(root->left), 1 + cmaxDepth(root->right));
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}