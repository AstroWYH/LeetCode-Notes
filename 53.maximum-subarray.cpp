/*
 * @lc app=leetcode.cn id=53 lang=cpp
 * @lcpr version=30204
 *
 * [53] 最大子数组和
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
//   public:
//     int maxSubArray(vector<int> &nums)
//     {
//         int max_sum = INT_MIN;
//         int sum = 0;
//         for (int i = 0; i < nums.size(); i++)
//         {
//             sum += nums[i];
//             max_sum = max(sum, max_sum);
//             if (sum < 0) // 这题最大的坑点，这句一定要放在max下面，否则无法处理数组全负的情况
//                 sum = 0;
//         }
//         return max_sum;
//     }
// };

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
      if (nums.size() == 0) return 0;
      if (nums.size() == 1) return nums[0];

      vector<int> dp(nums.size());
      dp[0] = nums[0];
      for (int i = 1; i < nums.size(); i++) {
        dp[i] = (dp[i - 1] > 0 ? dp[i - 1] : 0) + nums[i];
        // printf("dp[%d]:%d %d %d %d\n", i, dp[i], dp[i - 1], (dp[i - 1] > 0), nums[i]);
      }

      // for_each(dp.begin(), dp.end(), [](int& val) {
      //   cout << val << " ";
      // });

      return *max_element(dp.begin(), dp.end());
    }
};
// @lc code=end



/*
// @lcpr case=start
// [-2,1,-3,4,-1,2,1,-5,4]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

// @lcpr case=start
// [5,4,-1,7,8]\n
// @lcpr case=end

 */

