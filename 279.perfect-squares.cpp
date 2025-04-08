/*
 * @lc app=leetcode.cn id=279 lang=cpp
 * @lcpr version=30204
 *
 * [279] 完全平方数
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
  int numSquares(int n) {
    vector<int> dp(n + 1, INT_MAX); // 初始化dp数组
    dp[0] = 0;                                 // 基础情况

    for (int i = 1; i <= n; i++) {             // 遍历目标值i
      for (int j = 1; j * j <= i; j++) {       // 遍历可能的平方数j*j
        dp[i] = min(dp[i], dp[i - j * j] + 1); // 状态转移
      }
    }

    return dp[n];
  }
};

// 注意：i的目的是dp的必然遍历，填dp[]，也是问题。
// j的目的是拆分i的可能性，所以要内层遍历。

// 定义状态：
// dp[i] 表示和为 i 时所需的最少完全平方数数量。
// 初始化：
// dp[0] = 0（和为 0 不需要任何数）。
// 其他 dp[i] 初始化为 INT_MAX，表示暂时无法达到。

// 具体示例（以 n = 5 为例）
// 初始化：dp = [0, ∞, ∞, ∞, ∞, ∞]
// 逐步计算：

// i = 1：
// 可能的 j*j：1*1 = 1 dp[1] = min(∞, dp[0] + 1) = 1 更新后：dp = [0, 1, ∞, ∞,
// ∞, ∞] i = 2： 可能的 j*j：1*1 = 1 dp[2] = min(∞, dp[1] + 1) = 2 更新后：dp =
// [0, 1, 2, ∞, ∞, ∞] i = 3： 可能的 j*j：1*1 = 1 dp[3] = min(∞, dp[2] + 1) = 3
// 更新后：dp = [0, 1, 2, 3, ∞, ∞] i = 4： 可能的 j*j：1*1 = 1 和 2*2 = 4
// j=1：dp[4] = min(∞, dp[3] + 1) = 4
// j=2：dp[4] = min(4, dp[0] + 1) = 1 更新后：dp = [0, 1, 2, 3, 1, ∞]
// i = 5：
// 可能的 j*j：1*1 = 1 和 2*2 = 4
// j=1：dp[5] = min(∞, dp[4] + 1) = 2
// j=2：dp[5] = min(2, dp[1] + 1) = 2 最终结果：dp = [0, 1, 2, 3, 1, 2] 解释：5
// = 4 + 1（最少需要2个完全平方数）

// 为什么能保证最优解？
// 完全背包特性：每个完全平方数（物品）可以重复使用，因此内层循环遍历所有可能的
// j*j。 动态规划的无后效性：dp[i] 仅依赖于之前计算的 dp[i -
// j*j]，通过自底向上填表确保正确性

// 复杂度分析
// 时间复杂度：O(n√n)。外层循环 n 次，内层循环最多 √n 次（j*j ≤ n）。
// 空间复杂度：O(n)，用于存储 dp 数组

// @lc code=end

/*
// @lcpr case=start
// 12\n
// @lcpr case=end

// @lcpr case=start
// 13\n
// @lcpr case=end

 */
