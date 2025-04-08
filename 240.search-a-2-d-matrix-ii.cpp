/*
 * @lc app=leetcode.cn id=240 lang=cpp
 * @lcpr version=30204
 *
 * [240] 搜索二维矩阵 II
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
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();

    for (int i = 0; i < m; i++) {
      for (int j = n - 1; j >= 0; j--) {
        if (matrix[i][j] == target) {
          return true;
        } else if (matrix[i][j] < target) {
          break;
        }
      }
    }

    return false;
  }
};

// Z字形查找法（也称为"右上角出发法"）是最优解法，其核心思想是：
// 从矩阵的右上角（第一行最后一列）开始搜索
// 每次比较可以排除一整行或一整列，从而快速缩小搜索范围
// 时间复杂度O(m+n)，空间复杂度O(1)

// [
//     [1,   4,  7, 11, 15],
//     [2,   5,  8, 12, 19],
//     [3,   6,  9, 16, 22],
//     [10, 13, 14, 17, 24],
//     [18, 21, 23, 26, 30]
// ]

// 我们要查找target=5，下面是详细的搜索步骤：
// 起点：右上角(0,4)，值为15
// 15 > 5 → 向左移动至(0,3)，值为11
// 位置(0,3)，值为11
// 11 > 5 → 向左移动至(0,2)，值为7
// 位置(0,2)，值为7
// 7 > 5 → 向左移动至(0,1)，值为4
// 位置(0,1)，值为4
// 4 < 5 → 向下移动至(1,1)，值为5
// 位置(1,1)，值为5
// 5 == 5 → 找到目标，返回true 

// @lc code=end

/*
// @lcpr case=start
//
[[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]\n5\n
// @lcpr case=end

// @lcpr case=start
//
[[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]]\n20\n
// @lcpr case=end

 */
