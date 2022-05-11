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

二叉树 递归 深度优先搜索 DFS 后续遍历 栈

思路：经典-二叉树前序遍历-递归(DFS)解法，后续遍历：左-右-中。

递归关键点：
1）递归函数参数、返回值。此题不需要返回值，为void；参数为当前节点指针*cur，和统计结果的vec。
2）递归终止条件。此题为cur==nullptr，遍历到叶子节点后，再往下一层，cur就会为空（没有节点了）。
3）递归函数内逻辑。此题根据二叉树遍历方式（前、中、后序），来决定push(cur)、traverse(left)、
traverse(right)的执行顺序。

注：二叉树的“前、中、后序”的“递归解法”应作为模板记住，其余二叉树题目在此基础延伸。
注：二叉树的“迭代法”是通过“栈”实现，后续可以了解。
注：二叉树的struct TreeNode，和链表ListNode类似（多一个指针），应当会写才行。

class Solution {
public:
    void traverse(TreeNode* cur, vector<int>& vec) {
        if (cur == nullptr) return;
        traverse(cur->left, vec);
        traverse(cur->right, vec);
        vec.push_back(cur->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        traverse(root, result);
        return result;
    }
};