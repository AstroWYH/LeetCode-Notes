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
  bool isBlue(vector<int> &nums, int target, int i) {
    int end = nums[nums.size() - 1];
    if (nums[i] > end) {
      return target <= nums[i] && target > end;
    } else {
      return target <= nums[i] || target > end;
    }
  }

  int lowerBound(vector<int> &nums, int target) {
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
