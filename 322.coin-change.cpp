/*
 * @lc app=leetcode.cn id=322 lang=cpp
 * @lcpr version=30204
 *
 * [322] 零钱兑换
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
  int coinChange(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int coin : coins) {
      for (int i = coin; i <= amount; i++) {
        dp[i] = min(dp[i], dp[i - coin] + 1);
      }
    }

    return dp[amount] > amount ? -1 : dp[amount];
  }
};

// dp[]上来全部填满大值
// dp[]可能在不同的for的里，重新被覆盖填写，比如dp[2]一开始赋值后，可能后面遇到个更小的值
// dp[]可能前面有些值直接跳过了，比如dp[0]后，从dp[5]开始赋值，中间的略过都有可能
// 虽然还是复杂的两层for，但不再是第一层for为遍历i，而是遍历coins

// 1. 基本概念
// 首先明确几个关键点：

// dp[i]：凑出金额 i 所需的最少硬币数量
// coin：当前考虑的硬币面额
// dp[i - coin]：凑出金额 i - coin 所需的最少硬币数量
// 2. 方程拆解
// dp[i] = min(dp[i], dp[i - coin] + 1) 可以分解为：

// 第一部分：dp[i - coin] + 1
// 这表示：
// 先凑出 i - coin 金额（需要 dp[i - coin] 个硬币）
// 然后再加一个当前硬币（+1）
// 这样就得到了一个可能的凑出金额 i 的方案。

// 第二部分：min(dp[i], ...)
// 这表示：
// 将当前存储的方案和新发现的方案比较
// 保留硬币数更少的那个方案

// 3. 为什么这样设计？
// 硬币面额：[1, 2, 5]
// 当前计算 i = 6
// 正在考虑硬币 coin = 5

// 计算过程：
// i - coin = 1
// 已知 dp[1] = 1（用1个1元硬币）
// 新方案：dp[1] + 1 = 2（1元方案 + 1个5元）
// 与现有 dp[6] 比较：
// 可能已有方案是 dp[6] = 3（比如2+2+2）
// 取最小值 min(3, 2) = 2
// @lc code=end

/*
// @lcpr case=start
// [1, 2, 5]\n11\n
// @lcpr case=end

// @lcpr case=start
// [2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n0\n
// @lcpr case=end

 */
