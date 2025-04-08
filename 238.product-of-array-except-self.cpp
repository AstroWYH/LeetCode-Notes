/*
 * @lc app=leetcode.cn id=238 lang=cpp
 * @lcpr version=30204
 *
 * [238] 除自身以外数组的乘积
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
  vector<int> productExceptSelf(vector<int> &nums) {
    vector<int> ans(nums.size(), 1);

    int pre = 1;
    for (int i = 0; i < nums.size(); i++) {
      if (i == 0) {
        pre = 1;
        ans[i] = 1;
      } else {
        pre *= nums[i - 1];
        ans[i] = pre;
      }
    }

    int suf = 1;
    for (int i = nums.size() - 1; i >= 0; i--) {
      if (i == nums.size() - 1) {
        suf = 1;
        ans[i] *= suf;
      } else {
        suf *= nums[i + 1];
        ans[i] *= suf;
      }
    }

    return ans;
  }
};

// 解法更优雅，如果当前的nums[i]的不想体现到pre上。实操是需要先用pre给ans赋值，
// 再计算pre即可，即pre仍然计算了nums[i]，但没体现到ans上。
// 这样，就不需要写上面繁琐的if-else，以及nums[i-1/i+1]了。
class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    int n = nums.size();
    vector<int> ans(n, 1);

    // 第一步：计算前缀乘积（从左到右）
    int pre = 1;
    for (int i = 0; i < n; i++) {
      ans[i] = pre;   // answer[i] = nums[0] * ... * nums[i-1]
      pre *= nums[i]; // 更新前缀乘积
    }

    // 第二步：乘后缀乘积（从右到左）
    int suf = 1;
    for (int i = n - 1; i >= 0; i--) {
      ans[i] *= suf;  // answer[i] *= nums[i+1] * ... * nums[n-1]
      suf *= nums[i]; // 更新后缀乘积
    }

    return ans;
  }
};

// 初始化：answer = [1, 1, 1, 1]。

// 前缀乘积计算：
// i=0：answer[0] = 1（前面无元素），prefix = 1 * 1 = 1；
// i=1：answer[1] = 1（前缀是 nums[0]=1），prefix = 1 * 2 = 2；
// i=2：answer[2] = 2（前缀是 1*2），prefix = 2 * 3 = 6；
// i=3：answer[3] = 6（前缀是 1*2*3），prefix = 6 * 4 = 24。
// 此时 answer = [1, 1, 2, 6]（存储了每个位置左侧的乘积）。

// 后缀乘积计算：
// i=3：answer[3] *= 1（后面无元素），suffix = 1 * 4 = 4；
// i=2：answer[2] *= 4（后缀是 nums[3]=4），suffix = 4 * 3 = 12；
// i=1：answer[1] *= 12（后缀是 3*4），suffix = 12 * 2 = 24；
// i=0：answer[0] *= 24（后缀是 2*3*4），suffix = 24 * 1 = 24。

// 最终 answer(前缀*后缀) = [24, 12, 8, 6]（即 [2*3*4, 1*3*4, 1*2*4, 1*2*3]）。
// @lc code=end

/*
// @lcpr case=start
// [1,2,3,4]\n
// @lcpr case=end

// @lcpr case=start
// [-1,1,0,-3,3]\n
// @lcpr case=end

 */
