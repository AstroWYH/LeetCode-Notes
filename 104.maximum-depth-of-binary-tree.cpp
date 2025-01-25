/*
 * @lc app=leetcode.cn id=104 lang=cpp
 * @lcpr version=30204
 *
 * [104] 二叉树的最大深度
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
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
public:
  // 首先，这个函数maxDeppth直接返回ans，传入node，可见可以直接用来递归
  // 这个递归函数的目的，是求出自己的高度，自己的高度=max(l+r)+1，可见，这就是一般情况下，该递归函数的return
  // 边界条件是什么，如果自己是null，那么直接return 0
  int maxDepth1(TreeNode *root) {
    if (!root)
      return 0;

    int l = maxDepth(root->left);
    int r = maxDepth(root->right);
    return max(l, r) + 1;
  }

  // 这个的思路和上面不同，上面是用一个递归函数，在进去出来的过程中，要返回每层node的高度，最后返回到root时，知道了总高度。是在抵达了最深处，才开始正式计算高度，一路返回的过程中计算。
  // 而这个不一样，是使用一个全局的ans。主要是在递归进去的过程中，计算高度，维护一个cnt和ans，ans就是max(ans,cnt)，是全局的，cnt就是每次递归或每个node都有一样，可能感觉上一会大一会小，实际是因为不同node的cnt大小不一样，ans就记录最大的cnt。
  int ans = 0;

  void findMax(TreeNode *node, int cnt) {
    if (!node)
      return;
    cnt++;
    ans = max(cnt, ans);
    findMax(node->left, cnt);
    findMax(node->right, cnt);
  }

  int maxDepth(TreeNode *root) {
    findMax(root, 0);
    return ans;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,null,2]\n
// @lcpr case=end

 */
