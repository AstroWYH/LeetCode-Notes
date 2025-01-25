/*
 * @lc app=leetcode.cn id=33 lang=cpp
 * @lcpr version=30204
 *
 * [33] 搜索旋转排序数组
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
  // 所谓蓝色，是指nums[mid]在target及其右侧 target <= nums[i]
  // 红色，是指nums[mid]在target左侧 nums[i] < target
  // 蓝色/红色代表已经确定的区间，而他们中间的代表未确定的，需要在while()中不断询问确定
  bool isBlue(vector<int> &nums, int target, int i) {
    int end = nums[nums.size() - 1];
    if (nums[i] > end) {
      return target <= nums[i] && target > end;
    } else {
      return target <= nums[i] || target > end;
    }
  }

  int lowerBound(vector<int> &nums, int target) {
    // 开区间写法，理论上r =
    // nums.size()，但总是有最右侧元素为蓝色，所以r可以左移一位，排除最右侧的元素。不排除还有问题，因为nums[r]会越界
    int l = -1, r = nums.size() - 1;
    while (l + 1 < r) {
      int mid = l + (r - l) / 2;
      if (isBlue(nums, target, mid)) {
        r = mid;
      } else {
        l = mid;
      }
    }
    return r;
  }

  int search(vector<int> &nums, int target) {
    int start = lowerBound(nums, target);
    // 最终的结果，如果start==size，代表
    // [1 3 5 6] target = 8
    // [4 5 6 7 0 1 2] taret = 8
    
    // 如果target!=nums[start]
    // [4 5 6 8 0 1 2] target = 7
    if (start == nums.size() || target != nums[start]) {
      return -1;
    }
    return start;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [4,5,6,7,0,1,2]\n0\n
// @lcpr case=end

// @lcpr case=start
// [4,5,6,7,0,1,2]\n3\n
// @lcpr case=end

// @lcpr case=start
// [1]\n0\n
// @lcpr case=end

 */
