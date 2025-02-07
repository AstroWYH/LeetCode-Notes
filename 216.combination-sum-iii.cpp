// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=216 lang=cpp
 * @lcpr version=30204
 *
 * [216] 组合总和 III
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
//   // 这里可以优化，用n来减，这样，既不需要这个函数的开销了
//   bool isSatisfied(vector<int> &path, int &n) {
//     int sum = 0;
//     for (auto &val : path) {
//       sum += val;
//     }
//     return sum == n;
//   }

//   vector<vector<int>> combinationSum3(int k, int n) {
//     vector<int> path;
//     vector<vector<int>> ans;

//     auto dfs = [&](this auto &&dfs, int k, int n, int i) {
//       if (path.size() == k) {
//         if (isSatisfied(path, n))
//           ans.push_back(path);
//         return;
//       }

//       for (int j = i; j <= 9; j++) {
//         path.push_back(j);
//         dfs(k, n, j + 1);
//         path.pop_back();
//       }
//     };

//     dfs(k, n, 1);

//     return ans;
//   }
// };

// class Solution {
// public:
//   vector<vector<int>> combinationSum3(int k, int n) {
//     vector<int> path;
//     vector<vector<int>> ans;

//     auto dfs = [&](this auto &&dfs, int k, int n, int i) {
//       if (path.size() == k && n == 0) {
//         ans.push_back(path);
//         return;
//       }

//       for (int j = i; j <= 9; j++) {
//         path.push_back(j);
//         dfs(k, n - j, j + 1);
//         path.pop_back();
//       }
//     };

//     dfs(k, n, 1);

//     return ans;
//   }
// };

// 写法2是错误的，这个表达式的判断存在问题

class Solution {
public:
  vector<vector<int>> combinationSum3(int k, int n) {
    vector<int> path;
    vector<vector<int>> ans;
    dfs(k, n, 1, path, ans);
    return ans;
  }

private:
  void dfs(int k, int n, int start, vector<int> &path,
           vector<vector<int>> &ans) {
    if (path.size() == k && n == 0) {
      ans.push_back(path);
      return;
    }

    if (n < 0)
      return;
    
    // 写法1：j <= 9 - (k - path.size()) + 1
    // 写法2：(9 - j + 1) >= (k - path.size()) 错误
    for (int j = start; j <= 9 - (k - path.size()) + 1; j++) {
      path.push_back(j);
      dfs(k, n - j, j + 1, path, ans);
      path.pop_back();
    }
  }
};

// class Solution {
// private:
//     vector<vector<int>> result; // 存放结果集
//     vector<int> path; // 符合条件的结果
//     void backtracking(int targetSum, int k, int sum, int startIndex) {
//         if (sum > targetSum) { // 剪枝操作
//             return; 
//         }
//         if (path.size() == k) {
//             if (sum == targetSum) result.push_back(path);
//             return; // 如果path.size() == k 但sum != targetSum 直接返回
//         }
//         for (int i = startIndex; i <= 9 - (k - path.size()) + 1; i++) { // 剪枝
//             sum += i; // 处理
//             path.push_back(i); // 处理
//             backtracking(targetSum, k, sum, i + 1); // 注意i+1调整startIndex
//             sum -= i; // 回溯
//             path.pop_back(); // 回溯
//         }
//     }

// public:
//     vector<vector<int>> combinationSum3(int k, int n) {
//         result.clear(); // 可以不加
//         path.clear();   // 可以不加
//         backtracking(n, k, 0, 1);
//         return result;
//     }
// };
// @lc code=end

/*
// @lcpr case=start
// 3\n7\n
// @lcpr case=end

// @lcpr case=start
// 3\n9\n
// @lcpr case=end

// @lcpr case=start
// 4\n1\n
// @lcpr case=end

 */
