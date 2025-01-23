// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=200 lang=cpp
 * @lcpr version=30204
 *
 * [200] 岛屿数量
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
  // void dfs(int x, int y, vector<vector<char>> &grid) {
  //   if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size())
  //     return;
  //   走过的2和非岛屿的0，不进入
  //   if (grid[x][y] == '2' || grid[x][y] == '0')
  //     return;
  //   grid[x][y] = '2';
  //   dfs(x - 1, y, grid);
  //   dfs(x, y + 1, grid);
  //   dfs(x + 1, y, grid);
  //   dfs(x, y - 1, grid);
  // }

  // int numIslands(vector<vector<char>> &grid) {
  //   int total = 0;
  //   for (int i = 0; i < grid.size(); i++) {
  //     for (int j = 0; j < grid[0].size(); j++) {
  //       if (grid[i][j] == '1') {
  //         dfs(i, j, grid);
  //         total++;
  //       }
  //     }
  //   }
  //   return total;
  // }

  void bfs(int x, int y, vector<vector<char>> &grid) {
    queue<pair<int, int>> que;
    // que.push和grid占位2，操作时同步的
    que.push({x, y});
    grid[x][y] = '2';
    while (!que.empty()) {
      printf("que.size():%zu", que.size());
      int size = que.size();
      for (int i = 0; i < size; i++) {
        auto node = que.front();
        que.pop();
        int x = node.first;
        int y = node.second;
        // 进入前，判断好边界，然后que.push和grid占位2
        if (x - 1 >= 0 && grid[x - 1][y] == '1') {
          que.push({x - 1, y});
          grid[x - 1][y] = '2';
        }
        if (y + 1 < grid[0].size() && grid[x][y + 1] == '1') {
          que.push({x, y + 1});
          grid[x][y + 1] = '2';
        }
        if (x + 1 < grid.size() && grid[x + 1][y] == '1') {
          que.push({x + 1, y});
          grid[x + 1][y] = '2';
        }
        if (y - 1 >= 0 && grid[x][y - 1] == '1') {
          que.push({x, y - 1});
          grid[x][y - 1] = '2';
        }
      }
    }
  }

  int numIslands(vector<vector<char>> &grid) {
    int total = 0;
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid[0].size(); j++) {
        if (grid[i][j] == '1') {
          bfs(i, j, grid);
          total++;
        }
      }
    }
    return total;
  }
};
// @lc code=end

/*
// @lcpr case=start
//
[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]\n
// @lcpr case=end

// @lcpr case=start
//
[["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]\n
// @lcpr case=end

 */
