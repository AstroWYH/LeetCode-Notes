/*
 * @lc app=leetcode.cn id=153 lang=cpp
 * @lcpr version=30204
 *
 * [153] 寻找旋转排序数组中的最小值
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
  // 蓝色：最小值及其右侧
  // 红色：最小值左侧
  int findMin(vector<int> &nums) {
    // 开区间
    int l = -1, r = nums.size() - 1;
    int end = nums[r];
    while (l + 1 < r) {
      int mid = l + (r - l) / 2;
      if (nums[mid] > end) {
        l = mid;
      } else {
        r = mid;
      }
    }
    return nums[r];
  }
};
// @lc code=end

/*
// @lcpr case=start
// [3,4,5,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [4,5,6,7,0,1,2]\n
// @lcpr case=end

// @lcpr case=start
// [11,13,15,17]\n
// @lcpr case=end

 */
