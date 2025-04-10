/*
 * @lc app=leetcode.cn id=394 lang=cpp
 * @lcpr version=30204
 *
 * [394] 字符串解码
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
  string decodeString(string s) {
    stack<int> nums;
    stack<string> strs;
    string res;
    int num = 0;

    for (char c : s) {
      if (isdigit(c)) {
        num = num * 10 + (c - '0'); // 处理多位数
      } else if (isalpha(c)) {
        res += c; // 拼接字母
      } else if (c == '[') {
        nums.push(num);
        strs.push(res);
        num = 0;
        res.clear(); // 进入下一层
      } else if (c == ']') {
        int repeat = nums.top();
        nums.pop();
        string prev = strs.top();
        strs.pop();
        for (int i = 0; i < repeat; ++i) {
          prev += res; // 重复当前字符串
        }
        res = prev; // 更新为拼接后的结果
      }
    }
    return res;
  }
};
// 这题充分说明了，栈是可以模拟起到递归一层一层深入的效果的，遇到[就进入下一层，遇到]就返回上一层

// 以 3[a2[c]] 为例：
// 遇到 3 → num=3。
// 遇到 [ → nums=[3], strs=[""], 清空 res。
// 遇到 a → res="a"。
// 遇到 2 → num=2。
// 遇到 [ → nums=[3,2], strs=["", "a"], 清空 res。
// 遇到 c → res="c"。
// 遇到 ] → 弹出 2 和 "a", res="a" + "c"*2 = "acc"。
// 遇到 ] → 弹出 3 和 "", res="" + "acc"*3 = "accaccacc"。
// @lc code=end

/*
// @lcpr case=start
// "3[a]2[bc]"\n
// @lcpr case=end

// @lcpr case=start
// "3[a2[c]]"\n
// @lcpr case=end

// @lcpr case=start
// "2[abc]3[cd]ef"\n
// @lcpr case=end

// @lcpr case=start
// "abc3[cd]xyz"\n
// @lcpr case=end

 */
