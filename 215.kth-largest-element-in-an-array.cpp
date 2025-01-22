/*
 * @lc app=leetcode.cn id=215 lang=cpp
 * @lcpr version=30204
 *
 * [215] 数组中的第K个最大元素
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
// 快速选择的复杂度是O（n），因为是n+n/2+n/4+...1 = n
// 快速排序的复杂度是O（logn），因为每次哨兵是O（n），递归是O（logn）次

// 为什么快速选择是 O(n) 而不是 O(n log n)
// 与快速排序的区别:
// 快速排序需要对数组的每一部分都进行递归处理，因此总时间复杂度为 O(n log n)。
// 快速选择算法只需要递归处理其中一部分，因此总时间复杂度为 O(n)。
// 递归的规模:
// 快速选择算法每次递归处理的数组规模减半，但只需要处理其中一部分，因此递归的总规模是 O(n)。

class Solution {
public:
  int findKthLargest(vector<int> &nums, int k) { return quickSort(nums, k); }

  int quickSort(vector<int> &nums, int k) {
    int p = nums[rand() % nums.size()];

    vector<int> big;
    vector<int> equal;
    vector<int> small;

    // 哨兵，ON复杂度
    for (auto num : nums) {
      if (p < num)
        big.push_back(num);
      if (p == num)
        equal.push_back(num);
      if (p > num)
        small.push_back(num);
    }

    if (k <= big.size()) {
      return quickSort(big, k);
    }
    if (big.size() + equal.size() < k) {
      return quickSort(small, k - (big.size() + equal.size()));
    }

    return p;
  }
};
// @lc code=end

/*
// @lcpr case=start
// 2\n
// @lcpr case=end

// @lcpr case=start
// 4\n
// @lcpr case=end

 */
