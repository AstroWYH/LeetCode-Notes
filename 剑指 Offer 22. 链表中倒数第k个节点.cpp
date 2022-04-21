/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
// 第1种解法：先遍历链表得到长度n，然后走n-k即可
// wyh 此题理解一句话：head就是第0个链表的next指针，指向的第1个链表
// wyh node = head->next就是第1个链表的next指针，在此基础->next就是访问到第2个链表的指针
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* node = nullptr;
        int n = 0;
        for (node = head; node != nullptr; node = node->next) {
            n++;
        }
        for (node = head; n - k > 0; n--) {
            node = node->next;
        }
        return node;
    }
};

// 第2种解法：快慢双指针
// fast从k出发到n，slow同时从0出发，当fast到n时共走n-k，slow此时也共走n-k，剩下k，slow的位置就是题目想要的位置
class Solution {
public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode* fast = nullptr;
        ListNode* slow = nullptr;
        for (fast = head; k > 0; k--) {
            fast = fast->next;
        }
        for (slow = head; fast;) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};