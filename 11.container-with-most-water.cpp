/*
 * @lc app=leetcode.cn id=11 lang=cpp
 * @lcpr version=30204
 *
 * [11] 盛最多水的容器
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

// 唯一需要注意的地方是，是r-l而非r-l+1
class Solution {
public:
  int maxArea(vector<int> &height) {
    int l = 0, r = height.size() - 1;
    int max_area = -1;
    while (l < r) {
      max_area = max(max_area, (r - l) * min(height[l], height[r]));
      // cout << max_area << " " << l << " " << r << endl;
      height[l] < height[r] ? l++ : r--;
    }
    return max_area;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [1,8,6,2,5,4,8,3,7]\n
// @lcpr case=end

// @lcpr case=start
// [1,1]\n
// @lcpr case=end

 */
