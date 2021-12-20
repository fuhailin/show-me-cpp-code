/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
   public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string tree = "[";
        if (!root) return tree + "]";
        queue<TreeNode*> que;
        que.emplace(root);
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (node) {
                    tree += std::to_string(node->val) + ",";
                    que.emplace(node->left);
                    que.emplace(node->right);
                } else {
                    tree.push_back('n');
                    tree.push_back(',');
                }
            }
        }
        return tree + "]";
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.size() <= 2) {
            return nullptr;
        }
        vector<TreeNode*> nodes;
        // 分割字符串
        string tmp;
        for (int i = 1; i < data.size() - 1; i++) {
            if (data[i] == ',') {
                if (tmp == "n") {
                    nodes.push_back(nullptr);
                } else {
                    nodes.push_back(new TreeNode(std::stoi(tmp)));
                }
                tmp = "";
            } else {
                tmp += data[i];
            }
        }

        int j = 1;                                               // i每往后移动一位，j移动两位，j始终是当前i的左子下标
        for (int i = 0; j < nodes.size(); ++i) {                 // 肯定是j先到达边界，所以这里判断j < vec.size()
            if (!nodes[i]) continue;                             // vec[i]为null时跳过。
            if (j < nodes.size()) nodes[i]->left = nodes[j++];   // 当前j位置为i的左子树
            if (j < nodes.size()) nodes[i]->right = nodes[j++];  // 当前j位置为i的右子树
        }
        return nodes[0];
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));