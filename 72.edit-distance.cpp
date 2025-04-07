/*
 * @lc app=leetcode.cn id=72 lang=cpp
 * @lcpr version=30204
 *
 * [72] 编辑距离
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
int minDistance(string word1, string word2) {
  int m = word1.size(), n = word2.size();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

  // 初始化
  for (int i = 0; i <= m; i++)
    dp[i][0] = i;
  for (int j = 0; j <= n; j++)
    dp[0][j] = j;

  // 填表
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
      }
    }
  }
  return dp[m][n];
}

// 为什么是m+1, n+1，因为还要考虑空字符串

// 概述：
// 定义状态：
// dp[i][j] 表示 word1 的前 i 个字符变成 word2 的前 j 个字符的最小操作次数。
// 例如，dp[2][3] 表示 "ho" → "ros" 的最小操作数。
// 初始化：
// dp[0][j] = j：空字符串变 word2 的前 j 个字符，需要 j 次插入。
// dp[i][0] = i：word1 的前 i 个字符变空字符串，需要 i 次删除。
// 状态转移：
// 如果 word1[i-1] == word2[j-1]：
// 当前字符相同，无需操作，直接继承左上角的值：dp[i][j] = dp[i-1][j-1]。
// 如果 word1[i-1] != word2[j-1]：
// 插入：dp[i][j-1] + 1（在 word1 插入 word2[j-1]，匹配后跳过 j）。
// 删除：dp[i-1][j] + 1（删除 word1[i-1]，继续匹配 i-1）。
// 替换：dp[i-1][j-1] + 1（将 word1[i-1] 替换为 word2[j-1]）。
// 取三者最小值。

// 1）if逻辑
// word1 = "abc", word2 = "adc"，比较 i=2（'b'）和 j=2（'d'）时不同，但比较 i=3（'c'）和 j=3（'c'）时相同。
// 为什么直接继承左上角的值？
// 字符相同的意义：

// 当前字符已经匹配，不需要任何操作（无需插入、删除、替换）。
// 因此，总操作次数 = 前面字符的操作次数（即 dp[i-1][j-1]）。
// 动态规划表的含义：

// dp[i-1][j-1] 表示 word1 的前 i-1 个字符 → word2 的前 j-1 个字符的最小操作次数。
// 既然当前字符相同，直接沿用这个结果即可。

// 2）else逻辑
// 假设我们正在计算 word1 = "kkt" 和 word2 = "sit" 的编辑距离，当前处理到：

// i=2（word1 的前2个字符 "kk"）
// j=2（word2 的前2个字符 "si"）
// 目标是让 "kk" 变成 "si"。

// 插入操作的含义
// 操作步骤：

// 在 "kk" 的末尾插入 word2 的第 j 个字符 'i'，得到 "kki"。
// 此时 "kki" 的最后一个字符 'i' 已经和 word2 的 'i' 匹配，接下来只需计算 "kk" → "s" 的代价（即 dp[2][1]）。
// 动态规划表对应关系：

// dp[2][1]：表示 "kk" → "s" 的最小编辑距离（即删除 'k' 再替换 'k' 为 's'，假设代价为2）。
// 总代价 = 子问题代价 dp[2][1] + 本次插入操作代价 1 = 2 + 1 = 3。
// 为什么是 dp[i][j-1] + 1？
// dp[i][j-1]： 表示 word1 的前 i 个字符 → word2 的前 j-1 个字符的代价。 本例中即 "kk" → "s" 的代价。
// +1： 插入操作本身需要消耗1步（插入 'i'）。
// 与其他操作的对比
// 删除操作：
// 删除 'k'，计算 "k" → "si" 的代价（dp[1][2] + 1）。
// 替换操作：
// 替换 'k' 为 's'，计算 "k" → "s" 的代价（dp[1][1] + 1）。
// 最终选择三种操作中的最小代价  

// @lc code=end

/*
// @lcpr case=start
// "horse"\n"ros"\n
// @lcpr case=end

// @lcpr case=start
// "intention"\n"execution"\n
// @lcpr case=end

 */
