/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

二叉树 高度 后续遍历 递归 DFS

class Solution {
public:
    int getHeight(TreeNode* node, bool& is_balanced) {
        if (node == nullptr) return 0;
        int lval = getHeight(node->left, is_balanced);
        int rval = getHeight(node->right, is_balanced);
        if (abs(lval - rval) > 1) {
            is_balanced = false;
        }
        return 1 + max(lval, rval);
    }
    bool isBalanced(TreeNode* root) {
        bool ans = true;
        getHeight(root, ans);
        return ans;
    }
};