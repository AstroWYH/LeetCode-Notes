/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

链表 哈希 set

思路：要判断2个链表是否相交，遍历第1个链表时，用哈希set存储记录，遍历第2个链表时，看哈希set是否已经
存储过该链表，如果有则找到返回，没有则表示不想交，返回空。

注：2个“相交”的问题，需要想到“遍历第1个用哈希存储记录，遍历第2个时看是否记录过”。

注：此题又属于unordered_set的使用，需要学会，如果“仅仅存储记录某个数据是否出现过”，可以优先考虑unordered_set。
不用每次都想到unordered_map去，本题如果用哈希map，则就是记录{{ListNode* 1,A},{ListNode* 2,A},...}，
实际上跟unordered_set起的作用一样，还浪费了value，只有key起到效果，因为查找就是find(key)。
注：简单地，哈希set/map的查询，主要就是find(key)。如果不需要value，则没必要用哈希map，哈希set即可。

注：此题unordered_set<>中存的是ListNode*，而非ListNode。实际上“每个链表node的地址，都是独一无二的”，
足以区分，这样操作没有问题，而且更方便。

注：此题展示了链表遍历的最简形式，应当记住。并非所有情况都要考虑dummy_head，dummy_head主要用于，
当无头节点时，没法一个while()搞定遍历，而需要单独写一小段逻辑的场合，因为有时逻辑写成cur->next，
就会上来就跳过head，此时用dummy_head就能一个while()一气呵成搞定遍历。

无头节点：
        ListNode* cur = head; // cur初始指向head
        while (cur != nullptr) { // 当前node由cur表示，最后判空也是cur
            ...
            cur = cur->next;
        }
有头节点：
        ListNode* dummy_head = new ListNode(0);
        dummy_head->next = head;
        ListNode* cur = dummy_head; // cur初始指向dummy_head，cur->next指向head
        while (cur->next != nullptr) { // 当前node由cur->next表示，最后判空也是cur->next
            ...
            cur = cur->next;
        }

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode*> set;
        ListNode* cur = headA;
        while (cur != nullptr) {
            set.insert(cur);
            cur = cur->next;
        }
        cur = headB;
        while (cur != nullptr) {
            if (set.count(cur)) return cur; 
            cur = cur->next;
        }
        return nullptr;
    }
};