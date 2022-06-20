/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

二叉树 前序遍历 递归 DFS 深度优先遍历

思路：此题思路不易想到，参考题解：https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/

若root是p, q的最近公共祖先，则只可能为以下情况之一：
1）p和q在root的子树中，且分列root的异侧（即分别在左、右子树中）；
2）p=root，且q在root的左或右子树中；
3）q=root，且p在root的左或右子树中。

递归三部曲：
1）终止条件。
当越过叶节点，则直接返回null；
当root等于p,q，则直接返回root；
2）递推工作。
开启递归左子节点，返回值记为left；
开启递归右子节点，返回值记为right；
3）返回值。根据left和right，可展开为四种情况。
1 当left和right同时为空：说明root的左/右子树中都不包含p,q，返回null；
2 当left和right同时不为空：说明p,q分列在root的异侧（分别在左/右子树），因此root为最近公共祖先，返回root；
3 当left为空，right不为空：p,q都不在root的左子树中，直接返回right。但具体可分为两种情况：这两点其实不重要，理解就行。
3.1 p,q其中一个在root的右子树中，此时right指向p（假设为p）；
3.2 p,q两节点都在root的右子树中，此时right指向最近公共祖先节点；
4 当left不为空，right为空：与情况3同理。

注：需要从此题学到的，二叉树前序遍历的递归返回结果，即left、right，有种“从底层累积向上汇报”的感觉，
但实际上没有累积，没从底层往上一层，“虽然累积但是覆盖，类似1&&0=0的感觉，即累积、但轻装上阵向上汇报”的感觉。
此题返回值为TreeNode*，则可能返回nullptr、root、left、right，即虽从底往上累积，但返回的也无非就是这几样东西。

注：递归永远需要关注的是，“当前层node是谁”，在当前层的基础上进行node->left、node->right，搞清楚当前层node，
在此基础上再“递归深入、返回，不要迷失不知道在哪一层了”。

注：平时自己用node更容易理解，此题因为题干用的root。

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left == nullptr && right == nullptr) return nullptr; // 1
        if (left == nullptr) return right; // 3
        if (right == nullptr) return left; // 4
        return root; // 2 if(left != null and right != null)
    }
};