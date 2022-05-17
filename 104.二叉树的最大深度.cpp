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

二叉树 前序遍历 递归 DFS

思路：采用前序遍历的模板，递归函数新增2个参数(cnt：当前计数、ans：最终计数)，每进入一层递归，
则cnt++，并且更新ans最大值；每返回一层递归，则在返回前最后一步cnt--。

注：此题虽说用“前序遍历模板”，但是可见“左右遍历”的前后，都在进行“处理”，所以再次反映“处理”可能
是个模糊的概念，具体情况具体考虑。
注：cnt++和cnt--在递归的开始和结束位置，和“回溯法”的某些地方是相似的，也是合理的。
注：root为空的情况，可以先考虑别遗漏。

class Solution {
public:
    void traverse(TreeNode* node, int& cnt, int& ans) {
        if (node == nullptr) return;
        cnt++;
        ans = max(cnt, ans);
        traverse(node->left, cnt, ans);
        traverse(node->right, cnt, ans);
        cnt--;
    }
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int cnt = 0, ans = 0;
        traverse(root, cnt, ans);
        return ans;
    }
};

代码随想录的题解

思路：从底往上考虑累加树的高度，所以考虑后序遍历。到底遍历到空节点时返回高度0，然后不断向上攀升，
每层都会比较左右节点的高度，取最大值，最后递归叠加到root位置处即可。

注：此题“后序遍历”思路，可以据此考虑后序遍历的使用场景，也确实是在“左右递归”后进行的操作。
注：此题解不易想到，但可积累经验。“带返回值的递归”，就是如此“通过终止条件的return，一步步将结果叠加返回”。

class Solution {
public:
    int getDepth(TreeNode* node) {
        if (node == nullptr) return 0;
        int lval = getDepth(node->left);
        int rval = getDepth(node->right);
        return 1 + max(lval, rval);
    }
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return getDepth(root);
    }
};