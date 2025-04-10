/*
 * @lc app=leetcode.cn id=337 lang=cpp
 * @lcpr version=30204
 *
 * [337] 打家劫舍 III
 */

// @lcpr-template-start
using namespace std;
#include <algorithm>
#include <array>
#include <bitset>
#include <climits>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
// @lcpr-template-end
// @lc code=start
// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

class Solution {
public:
  pair<int, int> dfs(TreeNode *node) {
    if (node == nullptr)
      return {0, 0};

    auto [left_ans, no_left_ans] = dfs(node->left);
    auto [right_ans, no_right_ans] = dfs(node->right);

    int cur_ans = no_left_ans + no_right_ans + node->val;
    int no_cur_ans = max(left_ans, no_left_ans) + max(right_ans, no_right_ans);
    return {cur_ans, no_cur_ans};
  }

  int rob(TreeNode *root) {
    auto [cur_ans, no_cur_ans] = dfs(root);
    return max(cur_ans, no_cur_ans);
  }
};

// 动态规划 (可以说要很熟练，才能想清思路了)
// 即使是二叉树的dp，不是按dp[]来写代码，而是按照二叉树的dfs遍历来写
// 此外，可以看出，前中后序不重要，就是先写dfs(left/right)
// 返回left/right相关的值，再去计算return ans;

// 偷当前节点时：收益 = 当前节点的钱 + 左子节点“不偷”的收益 + 右子节点“不偷”的收益。
// 不偷当前节点时：收益 = 左子节点“偷或不偷”的最大值 + 右子节点“偷或不偷”的最大值。
// 最终结果：根节点“偷或不偷”两种情况的最大值。
// @lc code=end

/*
// @lcpr case=start
// [3,2,3,null,3,null,1]\n
// @lcpr case=end

// @lcpr case=start
// [3,4,5,1,3,null,1]\n
// @lcpr case=end

 */
