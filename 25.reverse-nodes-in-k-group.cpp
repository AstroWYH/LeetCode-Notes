// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=25 lang=cpp
 * @lcpr version=30204
 *
 * [25] K 个一组翻转链表
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

// Definition for singly-linked list.
// struct ListNode {
//   int val;
//   ListNode *next;
//   ListNode() : val(0), next(nullptr) {}
//   ListNode(int x) : val(x), next(nullptr) {}
//   ListNode(int x, ListNode *next) : val(x), next(next) {}
// };

class Solution {
public:
  pair<ListNode *, ListNode *> ReverseList(ListNode *head, int k) {
    ListNode *cur = head;
    ListNode *pre = nullptr;
    ListNode *tmp = nullptr;
    while (cur && k > 0) {
      tmp = cur->next;
      cur->next = pre;
      pre = cur;
      cur = tmp;
      k--;
    }
    return {pre, head};
  }

  pair<ListNode *, ListNode *> myReverse(ListNode *head, ListNode *tail) {
    ListNode *cur = head;
    ListNode *pre = nullptr;
    // 和模板的反转链表不同，这里通过pre!=tail结束，而非while(cur)结束
    while (pre != tail) {
      ListNode *tmp = cur->next;
      cur->next = pre;
      pre = cur;
      cur = tmp;
    }
    return {tail, head};
  }

  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *dummy = new ListNode();
    dummy->next = head;
    ListNode *cur = dummy;
    ListNode *pre = dummy;
    ListNode *tmp = nullptr;
    // 2层循环
    while (head) {
      // 把cur移到当前阶段末尾
      cur = pre;
      for (int i = 0; i < k; i++) {
        cur = cur->next;
        if (!cur)
          return dummy->next;
      }
      tmp = cur->next;
      // tie(head, cur) = myReverse(head, cur);
      tie(head, cur) = ReverseList(head, k);
      pre->next = head;
      cur->next = tmp;
      pre = cur;
      head = tmp;
    }
    return dummy->next;
  }
};
// @lc code=end

/*
// @lcpr case=start
// [1,2,3,4,5]\n2\n
// @lcpr case=end

// @lcpr case=start
// [1,2,3,4,5]\n3\n
// @lcpr case=end

 */
