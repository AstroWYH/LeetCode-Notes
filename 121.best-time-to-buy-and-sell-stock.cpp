/*
 * @lc app=leetcode.cn id=121 lang=cpp
 * @lcpr version=30204
 *
 * [121] 买卖股票的最佳时机
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
  int maxProfit(vector<int> &prices) {
    int max_val = 0;
    int cur_min = 0; // 这个最小值很重要，它在左侧被记录，无论右侧遍历到多大，它都起作用
    if (prices.size() >= 1)
      cur_min = prices[0];
    for (int i = 0; i < prices.size(); i++) {
      if (prices[i] < cur_min)
        cur_min = prices[i];
      max_val = max(max_val, prices[i] - cur_min);
    }
    return max_val;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [7,1,5,3,6,4]\n
// @lcpr case=end

// @lcpr case=start
// [7,6,4,3,1]\n
// @lcpr case=end

 */
