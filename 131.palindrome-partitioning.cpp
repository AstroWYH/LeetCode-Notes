/*
 * @lc app=leetcode.cn id=131 lang=cpp
 * @lcpr version=30204
 *
 * [131] 分割回文串
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

// 灵神提供了2种方式，面向输入和面向结果，这里直接看更通用的面向结果
// 根据回溯图，看ij的值，看for循环的横向变化，和深度上的纵向

class Solution {
    bool isPalindrome(string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) {
                return false;
            }
        }
        return true;
    }

public:
    vector<vector<string>> partition(string s) {
        int n = s.length();
        vector<vector<string>> ans;
        vector<string> path;

        auto dfs = [&](auto&& dfs, int i) {
            if (i == n) {
                ans.emplace_back(path);
                return;
            }
            for (int j = i; j < n; j++) { // 枚举子串的结束位置
                if (isPalindrome(s, i, j)) {
                    path.push_back(s.substr(i, j - i + 1));
                    dfs(dfs, j + 1);
                    path.pop_back(); // 恢复现场
                }
            }
        };

        dfs(dfs, 0);
        return ans;
    }
};
// @lc code=end

/*
// @lcpr case=start
// "aab"\n
// @lcpr case=end

// @lcpr case=start
// "a"\n
// @lcpr case=end

 */
