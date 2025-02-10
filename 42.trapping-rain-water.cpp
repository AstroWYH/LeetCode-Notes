// @lcpr-before-debug-begin




// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=42 lang=cpp
 * @lcpr version=30204
 *
 * [42] 接雨水
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

// 单调栈是一种栈数据结构的特殊用法，它可以维护一个单调递增或递减的序列。
// 在这个问题中，我们使用 单调递减栈 来帮助计算存水的区域。

// 解题思路
// 我们从左到右遍历 height 数组：

// 维护一个单调递减栈 st：
// 栈中存放的是 柱子的索引，并且它们所对应的高度是 单调递减的。
// 当遇到比栈顶柱子更高的柱子时：
// 说明可能会形成一个存水区域，我们需要计算这个区域的存水量。
// 计算存水量：
// 先弹出栈顶元素，作为存水区域的底部（bottom_h）。
// 如果栈为空，说明左侧没有界限，无法存水，直接跳过。
// 找到左侧的边界，即栈顶元素的索引 left。
// 计算存水高度：dh = min(height[left], height[i]) - bottom_h。
// 计算存水宽度：(i - left - 1)。
// 累加存水面积。

class Solution { 
public: 
    int trap(vector<int>& height) { 
        int ans = 0; 
        stack<int> st; 
        for (int i = 0; i < height.size(); i++) { 
            while (!st.empty() && height[i] >= height[st.top()]) { 
                int bottom_h = height[st.top()]; 
                st.pop(); 
                if (st.empty()) { 
                    break; 
                } 
                int left = st.top(); 
                int dh = min(height[left], height[i]) - bottom_h; // 面积的高 
                ans += dh * (i - left - 1); 
            } 
            st.push(i); 
        } 
        return ans; 
    } 
};
// @lc code=end



/*
// @lcpr case=start
// [0,1,0,2,1,0,1,3,2,1,2,1]\n
// @lcpr case=end

// @lcpr case=start
// [4,2,0,3,2,5]\n
// @lcpr case=end

 */

