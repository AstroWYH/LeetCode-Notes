/*
 * @lc app=leetcode.cn id=347 lang=cpp
 * @lcpr version=30204
 *
 * [347] 前 K 个高频元素
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
  vector<int> topKFrequent(vector<int> &nums, int k) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
      map[nums[i]] += 1;
    }
    // for (const auto &[key, val] : map) {
    //   cout << "[map] " << key << " " << val << endl;
    // }
    vector<int> keys;
    for (const auto &[key, val] : map) {
      keys.push_back(key);
    }
    // for (const int &key : keys) {
    //   cout << "[keys] " << key << endl;
    // }
    sort(keys.begin(), keys.end(),
         [&map](const int &a, const int &b) { return map[a] > map[b]; });
    return vector<int>(keys.begin(), keys.begin() + k);
  }
};

// 用哈希表存起来，然后将keys导出数组，然后根据哈希表的值(cnt)，来倒序排序keys，再取前k个
// @lc code=end

/*
// @lcpr case=start
// [1,1,1,2,2,3]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1]\n1\n
// @lcpr case=end

 */
