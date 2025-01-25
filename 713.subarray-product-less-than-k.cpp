/*
 * @lc app=leetcode.cn id=713 lang=cpp
 * @lcpr version=30204
 *
 * [713] 乘积小于 K 的子数组
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
  // 这个题的关键是，每走一步，要通过while来维护满足条件的队列
  // 然后是最关键的，需要计算此时以右端点为end的cnt，其实cnt=r-l+1

  // 只有这样才是思路最清晰的做法，否则可能不知道怎么解决重复记录的问题
  // 因为每走一步，只有右端点是更新的，所以“以右端点为end”，这个描述就不会重复
  int numSubarrayProductLessThanK(vector<int> &nums, int k) {
    int s = 1;
    int cnt = 0;
    unordered_set<int> set;
    for (int l = 0, r = 0; r < nums.size(); r++) {
      s *= nums[r];
      while (l <= r && s >= k) { // l<=r可以不用判断
        s /= nums[l];
        l++;
      }
      cnt += r - l + 1; // 这一步是关键
    }

    return cnt;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [10,5,2,6]\n100\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3]\n0\n
// @lcpr case=end

 */
