// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=15 lang=cpp
 * @lcpr version=30204
 *
 * [15] 三数之和
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
  vector<vector<int>> threeSum(vector<int> &nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] > 0)
        continue;
      // 这不容易想到，需要用i-1判断，不能用i+1，因为至少要计算一次
      if (i > 0 && nums[i] == nums[i - 1])
        continue;
      int target = -nums[i];
      int j = i + 1;
      int k = nums.size() - 1;
      while (j < k) {
        if (nums[j] + nums[k] > target) {
          k--;
        } else if (nums[j] + nums[k] < target) {
          j++;
        } else {
          // 这也是一样，要先保证计算一次，然后再移动
          res.push_back({nums[i], nums[j], nums[k]});
          // 这不容易想到，遇到相同的要一直移，j<k也是必要的判断，否则数组访问越界
          while (j < k && nums[j] == nums[j + 1])
            j++;
          while (j < k && nums[k] == nums[k - 1])
            k--;
          j++;
          k--;
        }
      }
    }
    return res;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [-1,0,1,2,-1,-4]\n
// @lcpr case=end

// @lcpr case=start
// [0,1,1]\n
// @lcpr case=end

// @lcpr case=start
// [0,0,0]\n
// @lcpr case=end

 */
