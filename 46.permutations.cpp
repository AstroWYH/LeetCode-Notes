/*
 * @lc app=leetcode.cn id=46 lang=cpp
 * @lcpr version=30204
 *
 * [46] 全排列
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

// 把used用哈希表存nums[i]，更好理解
// 全排列和组合的不同在于，for循环不用从start->size，而是0->size，每深入一层，都全部
// 重新罗列一遍，所以也不会有i,j，只有i

// 实际上，即使是组合的i,j，j也是从i到size
// 具体关注那层递归的i或j值是多少就行，不要去推i,j的值，容易头晕。因为对于组合的情况，
// 横向和纵向，i,j都可能会增大
class Solution {
public:
    vector<vector<int>> coms; // 这两个使用全局变量，可以让回溯函数的参数更少，看上去更简洁
    vector<int> com;
    void backtracking(vector<int>& nums, unordered_map<int, bool>& used) {
        if (com.size() == nums.size()) {
            coms.push_back(com);
            return;
        }
        for (int i = 0; i < nums.size(); i++) { // 如果是组合问题，这里就要用idx来随着递归深入，压缩范围
            if (used[nums[i]] == true) continue; // 排列问题的used，好好理解
            used[nums[i]] = true;
            com.push_back(nums[i]);
            backtracking(nums, used);
            com.pop_back();
            used[nums[i]] = false;
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        // vector<bool> used(nums.size(), false);
        unordered_map<int, bool> used;
        backtracking(nums, used);
        return coms;
    }
};
// @lc code=end



/*
// @lcpr case=start
// [1,2,3]\n
// @lcpr case=end

// @lcpr case=start
// [0,1]\n
// @lcpr case=end

// @lcpr case=start
// [1]\n
// @lcpr case=end

 */

