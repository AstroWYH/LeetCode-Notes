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

思路：二叉树高度问题，后续遍历从底向上，通过return一层一层叠加高度，“左右继续递归”时返回当前的
左右子树高度。如果中途出现左右高度差>1的情况，则记录is_balanced并返回。

注：“二叉树的高度问题”，此“后续遍历从底往上通过return叠加高度”应当作为一种模板记住。
注：代码随想录的解法核心也是上面这条，区别在于return返回-1，不使用is_balanced记录，而是一旦出现false，
则在“左右继续递归”的下一条各直接return -1，这样就会一直光速return到最早的递归，将-1返回出去。
注：此题和104.二叉树的最大深度有类似之处，都和“高度”有关。
注：is_balanced这个记录，类似vec(result)，都属于在递归中“摘取果实，在某些情况下得到结果值”，
而不被递归过程影响，应该记住这种思想。

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