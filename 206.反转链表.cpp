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

链表 双指针 递归

思路：双指针(pre、cur)遍历链表的过程中，画图理解，将每个节点指向后一个节点的指针，反过来指向前一个节点。

注：需要想到pre、cur，一前一后指针才好操作达到cur->next=pre的目的，所以这两个指针必须有；此外，如果
cur->next指向pre，那么怎么往后遍历，所以需要自然而然地想到，还需要一个tmp，提前记录cur->next，才好
让cur不断往后遍历。

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* cur = head;
        while (cur) {
            ListNode* tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }
};

自己凭记忆，通过双指针改的递归。

注：我的递归用了void作为返回，if-return的出口1直接干return，并在return前对result赋结果值pre，
这样又多需要一个成员变量result。出口2就是直接走到函数结束。好处是更直观方便理解。

注：应当总结递归的常见形式。
1）函数reverse会独立出来；
2）内部会自己调用自己；
3）最外层的调用通常是初始参数，并且参数的选取很重要，毕竟要套娃；
4）共有2个出口。出口1：到达最内层后，统计结果并返回return；出口2：中间层的正常返回return。

class Solution {
public:
    ListNode* result = nullptr;
    void reverse(ListNode* pre, ListNode* cur) {
        if (!cur) {
            result = pre;
            return;
        }
        ListNode* tmp = cur->next;
        cur->next = pre;
        pre = cur;
        cur = tmp;
        reverse(pre, cur);
    }

    ListNode* reverseList(ListNode* head) {
        // ListNode* pre = nullptr;
        // ListNode* cur = head;
        reverse(nullptr, head);
        return result;
    }
};

老师给的，双指针改的递归。

注：递归函数返回不再是void，而是ListNode*，出口1直接return 最终结果pre，出口2直接return 整个递归
函数，为什么敢这么return呢，因为递归函数reverse后面没有别的操作，到达最内层后最终结果pre会一层层地
return出去，每层不会进行操作，pre就会直接被带到最外层的reverse返回结果，不会出问题。

注：递归函数内部调用时，可以直接换参数(cur, tmp)，节约了2个步骤，这里是随机应变取巧。

class Solution {
public:
    ListNode* reverse(ListNode* pre, ListNode* cur) {
        if (!cur) return pre;
        ListNode* tmp = cur->next;
        cur->next = pre;
        // pre = cur;
        // cur = tmp;
        return reverse(cur, tmp);
    }

    ListNode* reverseList(ListNode* head) {
        // ListNode* pre = nullptr;
        // ListNode* cur = head;
        return reverse(nullptr, head);
    }
};

自己写的错误解法，画图思考，问题在于AddtoHead刚修改了(cur->next)->next的指向，然后后面的
cur->next = tmp又给改回来了，做无用功，导致最终dummy_node_reverse只会指向最后一个节点。

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* dummy_node = new ListNode();
        dummy_node->next = head;
        ListNode* dummy_node_reverse = new ListNode();
        ListNode* cur = dummy_node;
        while (cur->next != nullptr) {
            ListNode* tmp = cur->next->next;
            AddtoHead(dummy_node_reverse, cur->next);
            cur = cur->next;
            cur->next = tmp;
        }
        return dummy_node_reverse->next;
    }

    void AddtoHead(ListNode* &dummy_node_reverse, ListNode* &add_node) {
        ListNode* new_node = add_node;
        new_node->next = dummy_node_reverse->next;
        dummy_node_reverse->next = new_node;
    }
};