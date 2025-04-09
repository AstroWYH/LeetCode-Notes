/*
 * @lc app=leetcode.cn id=309 lang=cpp
 * @lcpr version=30204
 *
 * [309] 买卖股票的最佳时机含冷冻期
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
// class Solution {
// public:
//   int maxProfit(vector<int> &prices) {
//     if (prices.size() == 1)
//       return 0;
//     if (prices.size() == 2)
//       return max(0, prices[1] - prices[0]);

//     vector<int> dp(prices.size(), 0);
//     dp[0] = 0;
//     dp[1] = max(0, prices[1] - prices[0]);
//     dp[2] = max(max(dp[1], prices[2] - prices[0]), prices[2] - prices[1]);
//     for (int i = 3; i < prices.size(); i++) {
//       dp[i] =
//           max(max(dp[i - 1], dp[i - 2]), dp[i - 3] + prices[i] - prices[i -
//           1]);
//     }

//     return dp[prices.size() - 1];
//   }
// };
// 自己思路，只能对一部分

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    if (prices.empty())
      return 0;
    int n = prices.size();
    vector<vector<int>> dp(n, vector<int>(3));
    dp[0][0] = -prices[0]; // 持有股票
    dp[0][1] = 0;          // 冷冻期（第一天不可能）
    dp[0][2] = 0;          // 不持有且非冷冻期

    for (int i = 1; i < n; ++i) {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][2] - prices[i]);
      dp[i][1] = dp[i - 1][0] + prices[i];
      dp[i][2] = max(dp[i - 1][2], dp[i - 1][1]);
    }
    return max(dp[n - 1][1], dp[n - 1][2]); // 最后一天持有股票无意义
  }
};

// 状态定义：
// i 表示第i天
// s 表示状态：
// 0: 持有股票
// 1: 不持有股票，处于冷冻期（即当天卖出了股票）
// 2: 不持有股票，不处于冷冻期（可以买入）

// 1. dp[i][0] = max(dp[i-1][0], dp[i-1][2] - prices[i])
// 含义：第 i 天持有股票的最大利润来自两种可能：
// 前一天已经持有股票：dp[i-1][0]（今天不操作，保持持有）。
// 当天买入股票：必须从前一天的非冷冻期状态（dp[i-1][2]）买入，因此利润为 dp[i-1][2] - prices[i]。

// 2. dp[i][1] = dp[i-1][0] + prices[i]
// 含义：第 i 天卖出股票后的利润 = 前一天持有股票的利润 + 当天股票价格。
// 注意：只有当天卖出才会进入冷冻期，因此直接从前一天的持有状态转移。

// 3. dp[i][2] = max(dp[i-1][2], dp[i-1][1])
// 含义：第 i 天不持有股票且不在冷冻期的最大利润来自两种可能：

// @lc code=end

/*
// @lcpr case=start
// [1,2,3,0,2]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */
