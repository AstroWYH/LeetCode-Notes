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

思路：和104求最大深度是姊妹题，唯一区别在于记录ans的时机。此题同样使用cnt++/--，来随着前序遍历
的过程记录当前深度，当只有“当前节点node，其左右节点都空时”，才表示遇到“叶子节点”，此时才更新ans。

注：此题虽说用“前序遍历模板”，但是可见“左右遍历”的前后，都在进行“处理”，所以再次反映“处理”可能
是个模糊的概念，具体情况具体考虑。
注：cnt++和cnt--在递归的开始和结束位置，和“回溯法”的某些地方是相似的，也是合理的。
注：root为空的情况，可以先考虑别遗漏。

class Solution {
public:
    void traverse(TreeNode* node, int& cnt, int& ans) {
        if (node == nullptr) return;
        cnt++;
        if (node->left == nullptr && node->right == nullptr) {
            ans = min(ans, cnt);
        }
        traverse(node->left, cnt, ans);
        traverse(node->right, cnt, ans);
        cnt--;
    }
    int minDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        int cnt = 0, ans = INT_MAX;
        traverse(root, cnt, ans);
        return ans;
    }
};