/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

链表

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

解法1：不采用虚拟头节点，考虑head和非head的情况。

思路：遍历删除链表元素，画出链表图，将指向需要删除的链表节点的指针(cur->next)指向下一个链表节点即可
(cur->next->next)，注意需要单独处理head指向的链表节点，因为(cur->next上来就跳过了head)。

注：核心是当遇到要删除的链表节点时，cur->next = cur->next->next;
注：C++没有内存回收机制，最好用tmp=cur->next，再delete tmp释放删除的链表；
注：特殊情况是头节点head需要单独处理，因为cur->next上来就跳过了head；
注：遍历过程用while，如果正常遍历++就cur = cur->next，如果删除就cur->next = cur->next->next，
用if-else来处理这段逻辑，因为正常遍历和删除都“往前走了一步”，属于while的一个步骤；
注：麻烦的点在于判空，一般需要考虑head、head->next、cur、cur->next!=nullptr，凭感觉先写出来，
然后带入推导看哪里有问题，具体情况再具体考虑；
注：当关注cur->val/next时，条件注意是cur!=nullptr。当关注cur->next->val/next时，条件注意是
cur->next!=nullptr。


1：head为空的情况后面已经考虑了，就不用再单独写。

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // if (head == nullptr) return head; // wyh 1
        while (head != nullptr && head->val == val) {
            ListNode* tmp = head;
            head = head->next;
            delete tmp;
        }
        ListNode* cur = head;
        while (cur != nullptr && cur->next != nullptr) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        return head;
    }
};

解法2：采用虚拟头节点dummy_head。

思路：新增dummy_head虚拟头节点，指向head节点，然后只一个while循环解决完，因为此时第一个cur->next
就是head，不需要再单独处理head。

注：dummy_head的步骤比较关键，首先new()，然后连接head，然后赋值给cur。处理完成后，先用head接管
dummy_head->next，然后delete dummy_head，最后return head。

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy_head = new ListNode(0);
        dummy_head->next = head;
        ListNode* cur = dummy_head;
        while (cur->next != nullptr) {
            if (cur->next->val == val) {
                ListNode* tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            } else {
                cur = cur->next;
            }
        }
        head = dummy_head->next;
        delete dummy_head;
        return head;
    }
};