/*
 * @lc app=leetcode.cn id=78 lang=cpp
 * @lcpr version=30204
 *
 * [78] 子集
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
class Solution {
public:
  vector<int> path;
  vector<vector<int>> ans;

  void dfs(int i, vector<int> &nums) {
    if (i == nums.size()) {
      ans.push_back(path);
      return;
    }

    // 左边
    dfs(i + 1, nums);

    // 右边
    path.push_back(nums[i]);
    dfs(i + 1, nums);
    path.pop_back();
  }

  vector<vector<int>> subsets(vector<int> &nums) {
    dfs(0, nums);

    return ans;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */
