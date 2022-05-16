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

二叉树 后序遍历 递归 DFS

思路：对称二叉树，递归过程需要同时比较“外侧和内侧”两棵树，并将比较结果结合(&&)往回传递，
如果都为true则不说，如果有一次为false则一路往回都会返回false。

注：轴对称，需要考虑的是每次递归“外侧和内侧”的比较，狭隘地考虑比较每次root的左右节点，是不行的。
注：此题是一个好的例子，递归参数中往下传的不一定是root，也可能是left+right。
注：递归过程同时遍历left+right左右2个节点，看着唬人，其实也是符合逻辑的，比较对称问题，
不然应该如何比较轴对称呢。
注：此题可以看出，终止条件return是可以出现多个的，不仅仅是一个。“终止条件”考虑得比较多，要想清楚不能遗漏。
比如都比外侧的左右两个节点，它们如果一空一不空，直接false；如果都空，直接true；然后才是比值，如果val不同，
直接false。然后才是“内部逻辑”部分。
注：此题是“后续遍历”的变种，因为是有点类似左-右-中，实际上是外侧-内侧-中。
注：此题递归的返回类型是bool，属于“一层一层往回带出返回值”，也是常见的一种类型，
和之前返回root的情况不一样，这二者的区别在于“左右递归的时候，是否有返回值，并且会继续往回带”。
注：此题主函数最终的返回值，是递归函数的返回值，有时也可能是递归函数的参数，比如vec(result)这种。

注：递归三部曲。
1）参数和返回值。参数按如上所说，如果不是root，那么应该考虑到left+right进去递归。
此外，有时带个额外的参数，如vec(result)用来装结果，也是常见的。
2）终止条件。如上所说，不止一个终止条件，需要考虑清楚，几个“可以直接return的条件”都想到了，
再进入“内部逻辑”的部分。
3）内部逻辑。内部逻辑就是“外侧-内侧-中”，可见内部逻辑始终会包括“左右继续递归”这个关键部分。
然后就是“中的处理”，实际上中的处理是“比较淡化”的，而且“可能是没有固定套路和思想”的，
比如此题是直接“return左右继续递归的结果”。

class Solution {
public:
    bool compare(TreeNode* left, TreeNode* right) {
        if (left == nullptr && right != nullptr) return false;
        else if (left != nullptr && right == nullptr) return false;
        else if (left == nullptr && right == nullptr) return true;
        else if (left->val != right->val) return false;

        bool out_val = compare(left->left, right->right);
        bool in_val = compare(left->right, right->left);
        bool is_same = out_val && in_val;
        return is_same;
    }
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        bool result = compare(root->left, root->right);
        return result;
    }
};
// @lc code=end

