/*
 * @lc app=leetcode.cn id=17 lang=cpp
 * @lcpr version=30204
 *
 * [17] 电话号码的字母组合
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
// 此题是典型的回溯，首先需要自己构建map映射。然后写dfs，在递归的过程中，需要有一个变量，来记录当前递归到哪一层，也需要用它来判断边界条件，这里就是i，从0开始，到size结束，因为到size时，ans里已经收集了size-1个path。
// 此外，这里的path没有使用传统的path.push()/pop()在进入/返回，看起来会更加优雅。
class Solution {
public:
  unordered_map<char, string> map = {
      {'2', "abc"}, {'3', "def"},  {'4', "ghi"}, {'5', "jkl"},
      {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"},
  };

  string com;
  vector<string> ans;

  void dfs(string &digits, int i) {
    if (i == digits.length()) {
      ans.push_back(com);
      return;
    }

    for (auto &e : map[digits[i]]) {
      com[i] = e;
      dfs(digits, i + 1);
    }
  }

  vector<string> letterCombinations(string digits) {
    if (digits.empty())
      return ans;
    com.resize(digits.length(), 'a');
    dfs(digits, 0);
    return ans;
  }
};
// @lc code=end

/*
// @lcpr case=start
// "23"\n
// @lcpr case=end

// @lcpr case=start
// ""\n
// @lcpr case=end

// @lcpr case=start
// "2"\n
// @lcpr case=end

 */
