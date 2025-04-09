/*
 * @lc app=leetcode.cn id=287 lang=cpp
 * @lcpr version=30204
 *
 * [287] 寻找重复数
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
  int findDuplicate(vector<int> &nums) {
    int n = nums.size() - 1;
    int l = 1, r = n;
    while (l < r) {
      int mid = l + (r - l) / 2;
      int cnt = 0;
      for (int num : nums) {
        if (num <= mid)
          cnt++;
      }
      if (cnt > mid)
        r = mid;
      else
        l = mid + 1;
    }
    return l;
  }
};
// 二分法
// 抽屉原理的应用：二分查找法在这个问题中的应用非常巧妙，它不是在数组索引上进行二分，而是在数字的值域范围[1,n]上进行二分查找。

// 数字范围是[1, n]（示例中n=4，数字为1,2,3,4）。
// 数组有n+1个数（示例中5个数），但数字范围只有n个，因此至少有一个数字重复。

// 关键思想：
// 如果数组中≤mid的数字个数 > mid，说明在[1, mid]范围内数字出现了重复。
// 因为如果没有重复，[1,
// mid]范围内最多有mid个不同的数字（即1,2,...,mid），此时≤mid的数字个数应恰好等于mid。
// 如果统计结果超过mid，则说明[1, mid]中有数字被重复使用了。

// 以示例[1,3,4,2,2]，n=4，第一次迭代mid=2：
// 统计≤2的数字：1, 2, 2 → 共3个。
// 期望情况：如果没有重复，[1,2]范围内最多有2个数字（1和2），统计结果应为2。
// 实际结果：3 > 2，说明[1,2]中有数字重复（此处是2重复了两次）。
// 因此，重复数字一定在[1,2]区间内，下一步将搜索范围缩小到[1,2]。

// 为什么 r = mid 而不是 r = mid - 1？
// 当 cnt > mid 时，重复数可能在 [1, mid] 区间内，包括 mid。
// 例如：nums = [1,2,2,3]，mid = 2，cnt = 3（因为 1,2,2 ≤ 2），此时重复数是 2。
// 如果直接 r = mid - 1，会错误地排除 2。
// 因此，r = mid 保留 mid 的可能性，继续在 [1, mid] 中搜索。

class Solution {
public:
  int findDuplicate(vector<int> &nums) {
    int slow = 0, fast = 0;
    while (true) {
      slow = nums[slow];
      fast = nums[nums[fast]];
      if (slow == fast)
        break;
    }
    int find = 0;
    while (find != slow) {
      slow = nums[slow];
      find = nums[find];
    }
    return find;
  }
};

// 我好像有点懂了，等于说是，如果存在环，那么如果一开始快慢指针一个走一步一个走两步，相遇后，那个位置很重要，然后慢指针从0开始走，快指针用慢指针的速度从相遇位置继续走，再次碰头，就是环入口，是吗，因为之前快指针多跑了可能很多圈追上了慢指针，这个位置很关键，从数学上，可以证明，此时他们一个从头走，一个继续走，同样速度，会在入口相遇，对吗？

// 对的！你的理解完全正确！让我用更形象的方式总结一下这个精妙的算法：
// 1. 快慢指针赛跑（检测环）
// 慢指针每次走1步，快指针每次走2步
// 如果存在环，快指针最终会从后面追上慢指针（就像跑步套圈）
// 相遇点：这个位置的关键在于，快指针可能已经绕环多跑了n圈
// 例如：操场跑步，快的人最终会追上慢的人，此时快的人可能已经多跑了若干圈

// 2. 寻找入口的魔法（数学原理简化版）
// 设：起点到环入口距离为L，环周长为C，相遇点距入口D

// 第一次相遇时：
// 慢指针走了：L + D
// 快指针走了：L + D + nC（多跑了n圈）
// 因为快指针速度是2倍：2(L+D) = L+D+nC → 化简得：L = nC - D
// 关键结论：
// 从起点走L步 = 从相遇点走nC - D步
// （两者都会到达环入口！）

// 3. 第二次同步走（验证入口）
// 慢指针回到起点，快指针留在相遇点
// 两者同速前进：
// 慢指针走L步到达入口
// 快指针走nC - D步（相当于绕环n圈后退回D步）也到达入口
// 必然在入口处相遇！
// @lc code=end

/*
// @lcpr case=start
// [1,3,4,2,2]\n
// @lcpr case=end

// @lcpr case=start
// [3,1,3,4,2]\n
// @lcpr case=end

// @lcpr case=start
// [3,3,3,3,3]\n
// @lcpr case=end

 */
