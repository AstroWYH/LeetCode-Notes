/*
 * @lc app=leetcode.cn id=236 lang=cpp
 * @lcpr version=30204
 *
 * [236] 二叉树的最近公共祖先
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
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  TreeNode *dfs(TreeNode *node, TreeNode *p, TreeNode *q) {
    if (node == nullptr)
      return nullptr;
    if (node == p || node == q)
      return node;

    TreeNode *l = dfs(node->left, p, q);
    TreeNode *r = dfs(node->right, p, q);

    if (l == nullptr && r == nullptr)
      return nullptr;
    if (l == nullptr)
      return r;
    if (r == nullptr)
      return l;
    return node;
  }

  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    return dfs(root, p, q);
  }
};
// @lc code=end

/*
// @lcpr case=start
// [3,5,1,6,2,0,8,null,null,7,4]\n5\n1\n
// @lcpr case=end

// @lcpr case=start
// [3,5,1,6,2,0,8,null,null,7,4]\n5\n4\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n1\n2\n
// @lcpr case=end

 */
