/*
 * @lc app=leetcode.cn id=51 lang=cpp
 * @lcpr version=30204
 *
 * [51] N 皇后
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

// 问：本题和 46. 全排列 的关系是什么？
// 答：由于每行恰好放一个皇后，记录每行的皇后放在哪一列，可以得到一个 [0,n−1] 的排列 queens。示例 1 的两个图，分别对应排列 [1,3,0,2] 和 [2,0,3,1]。所以我们本质上是在枚举列号的全排列。
// 问：如何 O(1) 判断两个皇后互相攻击？
// 答：由于我们保证了每行每列恰好放一个皇后，所以只需检查斜方向。对于 ↗ 方向的格子，行号加列号是不变的。对于 ↖ 方向的格子，行号减列号是不变的。如果两个皇后，行号加列号相同，或者行号减列号相同，那么这两个皇后互相攻击。
// 问：如何 O(1) 判断当前位置被之前放置的某个皇后攻击到？
// 答：额外用两个数组 diag 
// 1
//   和 diag 
// 2
//   分别标记之前放置的皇后的行号加列号，以及行号减列号。如果当前位置的行号加列号在 diag 
// 1
//   中（标记为 true），或者当前位置的行号减列号在 diag 
// 2
//   中（标记为 true），那么当前位置被之前放置的皇后攻击到，不能放皇后。

// 这道题是经典的 N皇后问题，要求在一个 
// 𝑛
// ×
// 𝑛
// n×n 的棋盘上摆放 
// 𝑛
// n 个皇后，使得它们互不攻击。即每个皇后所在的行、列和斜线都不能有其他皇后。我们的目标是返回所有可能的解决方案。

// 思路分析
// 我们可以采用 回溯法 来解决这个问题。回溯法是一种试探性的方法，通过在搜索树中构建解的路径，并在某一步发现路径不可行时回退，从而尝试其他可能的路径。

// 1. 状态建模
// 我们可以把问题抽象为：在棋盘上，每一行放置一个皇后，我们需要确定每一行皇后的位置，并且保证这些位置不会导致任何两个皇后互相攻击。

// 行（Row）：我们从第一行开始，逐行往下放置皇后，直到所有行都有皇后放置。
// 列（Column）：在每一行中，我们需要选择一个列来放置皇后，但需要保证这个列没有被其他行的皇后占用。
// 斜线（Diagonal）：除了列的冲突，我们还要避免两个皇后在同一条对角线（斜线）上。棋盘上有两条斜线：
// 从左上到右下的斜线，索引为 r - c（行减去列）。
// 从右上到左下的斜线，索引为 r + c（行加上列）。
// 2. 数据结构
// queens 数组：用来记录每行皇后的位置，queens[i] 表示第 i 行的皇后放在第 queens[i] 列。
// col 数组：用来记录某一列是否已经被占用，col[c] = 1 表示第 c 列已被某行的皇后占用。
// diag1 数组：用来记录从左上到右下的斜线是否被占用，diag1[r - c + (n - 1)] = 1 表示 r 行 c 列的斜线已被占用。
// diag2 数组：用来记录从右上到左下的斜线是否被占用，diag2[r + c] = 1 表示 r 行 c 列的斜线已被占用。
// 3. 回溯过程
// 递归函数：从第一行开始，逐行放置皇后。在每一行中，我们遍历所有列，尝试把皇后放在当前行的每个位置。
// 合法性检查：在尝试放置皇后之前，我们需要检查当前列和两条斜线是否已经有皇后。如果没有冲突，我们就可以放置皇后。
// 回溯：当我们成功地在当前行放置皇后后，递归进入下一行。如果当前行无法放置皇后（所有列都被占用），我们就回到上一个已放置皇后的行，尝试其他可能性。
// 终止条件：当我们成功放置了所有 
// 𝑛
// n 个皇后，即递归的行数等于 
// 𝑛
// n 时，说明找到一个解。此时将当前的棋盘配置保存下来。
// 4. 具体实现

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<int> queens(n); // 皇后放在 (r, queens[r])
        vector<int> col(n), diag1(n * 2 - 1), diag2(n * 2 - 1); // 检查列和两条斜线
        auto dfs = [&](this auto&& dfs, int r) {
            if (r == n) {
                // 当行数达到 n，表示找到一个解，构造棋盘的字符串表示
                vector<string> board(n);
                for (int i = 0; i < n; i++) {
                    board[i] = string(queens[i], '.') + 'Q' + string(n - 1 - queens[i], '.');
                }
                ans.push_back(board);
                return;
            }
            // 在第 r 行尝试放置皇后
            for (int c = 0; c < n; c++) {
                int rc = r - c + n - 1; // 计算左上到右下的斜线编号
                if (!col[c] && !diag1[r + c] && !diag2[rc]) { // 判断当前列和斜线是否已被占用
                    queens[r] = c; // 放置皇后
                    col[c] = diag1[r + c] = diag2[rc] = true; // 标记占用列和斜线
                    dfs(r + 1); // 尝试放置下一行的皇后
                    col[c] = diag1[r + c] = diag2[rc] = false; // 恢复现场，回溯
                }
            }
        };
        dfs(0); // 从第 0 行开始递归
        return ans;
    }
};

// @lc code=end



/*
// @lcpr case=start
// 4\n
// @lcpr case=end

// @lcpr case=start
// 1\n
// @lcpr case=end

 */

