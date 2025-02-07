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

// 写法2是错误的，这个表达式的判断存在问题，问题出在path的size那里，给path加一下int就对了

// class Solution {
// public:
//   vector<vector<int>> combinationSum3(int k, int n) {
//     vector<int> path;
//     vector<vector<int>> ans;
//     dfs(k, n, 1, path, ans);
//     return ans;
//   }

// private:
//   void dfs(int k, int n, int start, vector<int> &path,
//            vector<vector<int>> &ans) {
//     if (path.size() == k && n == 0) {
//       ans.push_back(path);
//       return;
//     }

//     if (n < 0)
//       return;
    
//     // 写法1：j <= 9 - (k - path.size()) + 1
//     // 写法2：(9 - j + 1) >= (k - path.size()) 错误 (9 - j + 1) >= (k - (int)path.size())
//     for (int j = start; j <= 9 - (k - path.size()) + 1; j++) {
//       path.push_back(j);
//       dfs(k, n - j, j + 1, path, ans);
//       path.pop_back();
//     }
//   }
// };

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

// 灵神解法，倒序更容易理解剪枝
// 灵神的剪枝很彻底，还有一个t > (i * 2 - d + 1) * d / 2，表达的意思是
// 剩余的数全部加起来也不够大，就剪掉，这是用了规律得出的公式
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> path;
        auto dfs = [&](this auto&& dfs, int i, int t) {
            int d = k - path.size(); // 还要选 d 个数
            if (t < 0 || t > (i * 2 - d + 1) * d / 2) { // 剪枝
                return;
            }
            if (d == 0) { // 找到一个合法组合
                ans.emplace_back(path);
                return;
            }
            for (int j = i; j >= d; j--) {
                path.push_back(j);
                dfs(j - 1, t - j);
                path.pop_back();
            }
        };
        dfs(9, n);
        return ans;
    }
};
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
