/*
 * @lc app=leetcode.cn id=338 lang=cpp
 * @lcpr version=30204
 *
 * [338] 比特位计数
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
//   vector<int> countBits(int n) {
//     vector<int> dp(n + 1, 0);
//     for (int i = 1; i <= n; ++i) {
//       dp[i] = dp[i >> 1] + (i & 1); // i>>1等价于i/2，i&1等价于i%2
//     }
//     return dp;
//   }
// };
// 此题的dp比较难想了，如果不知道技巧的话。

class Solution {
public:
  vector<int> countBits(int n) {
    vector<int> ans(n + 1, 0);

    for (int i = 1; i <= n; i++) {
      int num = i;
      while (num > 0) {
        if ((num & 1) == 1) {
          // cout << i << endl;
          ans[i]++;
        }
        // cout << "num before：" << num << endl;
        num >>= 1;
        // cout << "num：" << num << endl;
      }
    }

    return ans;
  }
};

// 怎么把十进制转换成二进制：右移 >>
// @lc code=end

/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 5\n
// @lcpr case=end

 */
