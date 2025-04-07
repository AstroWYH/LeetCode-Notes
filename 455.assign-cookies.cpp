/*
 * @lc app=leetcode.cn id=455 lang=cpp
 * @lcpr version=30204
 *
 * [455] 分发饼干
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
  int findContentChildren(vector<int> &g, vector<int> &s) {
    // 以s(饼干)遍历，行不通。因为饼干并不是一定会--，当前饼干可能下一轮还会用
    // int ptr = g.size() - 1;
    // int cnt = 0;
    // for (int i = s.size() - 1; i >= 0; i--) {
    //   if (s[i] >= g[ptr]) {
    //     cnt++;
    //   }
    //   ptr--;
    //   if (ptr < 0) break;
    // }
    // return cnt;

    // 以g(孩子胃口, 即问题)遍历
    if (s.size() == 0 || g.size() == 0)
      return 0;
    // 先排序
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    
    int ptr = s.size() - 1;
    int cnt = 0;
    for (int i = g.size() - 1; i >= 0; i--) {
      if (s[ptr] >= g[i]) {
        cnt++;
        ptr--;
        if (ptr < 0)
          break;
      }
    }
    return cnt;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [1,2,3]\n[1,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2]\n[1,2,3]\n
// @lcpr case=end

 */
