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

思路：此题是二叉树前序遍历的应用，直接在“前序遍历模板”的基础上，将中-左-右的“中”处理节点“记录节点到vec”替换成“swap左右节点”即可。

注：此题题解提到，前序遍历、后序遍历都是可以的，但中序遍历会翻转两次，可以尝试。另外，“递归”和“迭代”法都可以，可优先选用“递归”。
注：二叉树的题，上来就应该“优先考虑”“最直观的前序遍历”是否能解。
注：此题不像常见的递归模板，因为不是在其内部“单独定义一个递归函数来调用”，而是直接将题干函数拿来递归，对比前序遍历模板可发现，因为此题
没有vec(result)需要记录，此外返回值要么void，要么返回“每次当前的根节点root”，递归走完回来的时候，root实际上没变，
这样的返回值是可控的，因此就有了直接将“题干函数”用来递归的写法。
注：前、中、后序遍历实际上区别在于“中节点的处理时机”，而且观察内部逻辑写法会发现，“中节点总是在处理”，另外“左、右节点则是在调递归函数”，
这点很重要。
注：“递归三部曲”回顾：终止条件、参数和返回值、内部逻辑。
注：swap很好用，其内部有很多重载，所以直接传指针，也会帮忙交换指针指向的内容。

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;
        swap(root->left, root->right);
        invertTree(root->left);
        invertTree(root->right);
        return root;
    }
};