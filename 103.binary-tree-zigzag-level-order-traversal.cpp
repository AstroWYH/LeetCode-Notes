// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=103 lang=cpp
 * @lcpr version=30204
 *
 * [103] 二叉树的锯齿形层序遍历
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
// struct TreeNode {
//   int val;
//   TreeNode *left;
//   TreeNode *right;
//   TreeNode() : val(0), left(nullptr), right(nullptr) {}
//   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
//   TreeNode(int x, TreeNode *left, TreeNode *right)
//       : val(x), left(left), right(right) {}
// };

class Solution {
public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    vector<vector<int>> coms;
    if (root == nullptr) return coms;
    deque<TreeNode *> que;
    que.push_back(root);
    int level = 0;
    while (!que.empty()) {
      // 遍历所有层
      deque<int> com;
      int size = que.size();
      while (size > 0) {
        // 遍历某层
        auto *node = que.front();
        if (node->left) {
          que.push_back(node->left);
        }
        if (node->right) {
          que.push_back(node->right);
        }
        que.pop_front();
        size--;
        if (level % 2)
          com.push_front(node->val);
        else
          com.push_back(node->val);
      }
      vector<int> ans;
      ans.assign(com.begin(), com.end());
      coms.push_back(ans);
      level++;
    }

    return coms;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [3,9,20,null,null,15,7]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

// @lcpr case=start
// []\n
// @lcpr case=end

 */
