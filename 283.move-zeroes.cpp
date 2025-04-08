/*
 * @lc app=leetcode.cn id=283 lang=cpp
 * @lcpr version=30204
 *
 * [283] 移动零
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
//   void moveZeroes(vector<int> &nums) {
//     int idx = 0;
//     bool bexsit = false;

//     for (int i = 0; i < nums.size(); i++) {
//       if (nums[i] == 0 && !bexsit) {
//         bexsit = true;
//         idx = i;
//       } else if (nums[i] != 0 && bexsit) {
//         nums[idx++] = nums[i];
//         nums[i] = 0;
//       }
//     }
//   }
// };

// 自己琢磨的解法：
// 1.如果遍历过程中，完全没遇到过0，则一直遍历，不做任何处理
// 2.但凡遇到一次0，则记录该0的idx，后续遇到非零值nums[i]，则将其覆盖到idx，将nums[i]置0

// 这里有个很巧妙的地方，每次发生“交换”，idx++，这里有2种情况：
// 1）比如0 2 5，这种交换（两步）直接变成2 0
// 5，所以idx++是合理的，idx仍然指着0；然后变成2 5 0，没问题 2）比如0 0
// 5，这种交换（一步）变成5 0 0，结果此时idx恰好指着中间的0，也没问题

// class Solution {
// public:
//   void moveZeroes(vector<int> &nums) {
//     int slow = 0, fast = 0;
//     int cnt = 0;

//     for (; fast < nums.size(); fast++) {
//       if (nums[fast] != 0) {
//         nums[slow++] = nums[fast];
//         cnt++;
//       }
//     }

//     for (int i = slow; i < nums.size(); i++) {
//       nums[i] = 0;
//     }
//   }
// };
// 快慢双指针，快指针遇到非零值，就赋值给慢指针，第二轮for慢指针及后续都置0

class Solution {
public:
  void moveZeroes(vector<int> &nums) {
    int slow = 0;

    for (int fast = 0; fast < nums.size(); fast++) {
      if (nums[fast] != 0) {
        swap(nums[fast], nums[slow++]);
      }
    }
  }
};
// 最简单的办法，快慢双指针，快指针遇到非零值，就和慢指针swap

// @lc code=end

/*
// @lcpr case=start
// [0,1,0,3,12]\n
// @lcpr case=end

// @lcpr case=start
// [0]\n
// @lcpr case=end

 */
