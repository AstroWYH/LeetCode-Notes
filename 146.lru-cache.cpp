// @lcpr-before-debug-begin

// @lcpr-before-debug-end

/*
 * @lc app=leetcode.cn id=146 lang=cpp
 * @lcpr version=30204
 *
 * [146] LRU 缓存
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
class DLinkNode {
public:
  DLinkNode() {}
  DLinkNode(int in_key, int in_val) : key(in_key), val(in_val) {}
  int key = 0;
  int val = 0;
  DLinkNode *next = nullptr;
  DLinkNode *prev = nullptr;
};

class LRUCache {
public:
  int capacity_ = 0;
  int size_ = 0;

  unordered_map<int, DLinkNode *> lru_map;

  DLinkNode *head = nullptr;
  DLinkNode *tail = nullptr;

  LRUCache(int capacity) {
    capacity_ = capacity;
    head = new DLinkNode();
    tail = new DLinkNode();
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    // 如果存在
    if (lru_map.count(key)) {
      DLinkNode *node = lru_map[key];
      // 如果node就在head后面
      if (node->prev == head) {
        return node->val;
      }
      // 放到head后面
      // 断开node自己
      node->next->prev = node->prev;
      node->prev->next = node->next;

      // 放到head后面
      head->next->prev = node;
      node->next = head->next;
      node->prev = head;
      head->next = node;

      return node->val;
    }
    return -1;
  }

  void put(int key, int value) {
    if (lru_map.count(key)) {
      DLinkNode *node = lru_map[key];
      node->val = value;

      // 放到head后面
      // 断开node自己
      node->next->prev = node->prev;
      node->prev->next = node->next;

      // 放到head后面
      head->next->prev = node;
      node->next = head->next;
      node->prev = head;
      head->next = node;
    } else {
      DLinkNode *node = new DLinkNode(key, value);
      size_++;
      lru_map.insert({key, node});

      // 放到head后面
      head->next->prev = node;
      node->next = head->next;
      node->prev = head;
      head->next = node;

      if (size_ > capacity_) {
        DLinkNode *last_node = tail->prev;
        // 删除tail前面的node
        last_node->prev->next = tail;
        tail->prev = last_node->prev;
        size_--;
        lru_map.erase(last_node->key);
        delete last_node;
      }
    }
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end
