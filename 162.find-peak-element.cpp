/*
 * @lc app=leetcode.cn id=162 lang=cpp
 * @lcpr version=30204
 *
 * [162] 寻找峰值
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
  // 蓝色：峰值及其右侧
  // 红色：峰值左侧
  int findPeakElement(vector<int> &nums) {
    // 开区间
    int l = -1, r = nums.size() - 1;
    while (l + 1 < r) {
      int mid = l + (r - l) / 2;
      // mid+1不会越界，因为最终是(l,r)的开区间，此时(l+r)/2=l，所以l+1=r，不会越界
      if (nums[mid] < nums[mid + 1]) {
        l = mid;
      } else {
        r = mid;
      }
    }
    return r;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [1,2,3,1]\n
// @lcpr case=end

// @lcpr case=start
// [1,2,1,3,5,6,4]\n
// @lcpr case=end

 */
