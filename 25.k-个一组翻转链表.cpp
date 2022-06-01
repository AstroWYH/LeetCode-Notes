链表

思路：需要把链表节点k个一组分组，可使用一个指针head依次指向每组的头节点。这个指针每次向前移动k步，直至链表结尾。
对于每个分组，先判断其长度是否大于等于k。若是，则翻转这部分链表，否则不需要翻转。
接下来的问题就是如何翻转一个分组内的子链表。翻转一个链表并不难，可参考「206. 反转链表」。
但是对于一个子链表，除了翻转其本身之外，还需要将子链表的头部与上一个子链表连接，以及子链表的尾部与下一个子链表连接。

注：此题细节复杂，记住「206. 反转链表」解法即可。

class Solution {
public:
    // 翻转一个子链表，并且返回新的头与尾
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail) {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return {tail, head};
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* hair = new ListNode(0);
        hair->next = head;
        ListNode* pre = hair;

        while (head) {
            ListNode* tail = pre;
            // 查看剩余部分长度是否大于等于 k
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    return hair->next;
                }
            }
            ListNode* nex = tail->next;
            // 这里是 C++17 的写法，也可以写成
            // pair<ListNode*, ListNode*> result = myReverse(head, tail);
            // head = result.first;
            // tail = result.second;
            tie(head, tail) = myReverse(head, tail);
            // 把子链表重新接回原链表
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }

        return hair->next;
    }
};

// 自己的错误解法

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
class Solution {
public:
    int cnt = 0;
    void reverseList(ListNode* pre_node, ListNode* cur_node, int k,
        ListNode* &last_head, ListNode* &final_head) {
        ++cnt;
        // if (cnt == 3) return;
        int last_k = k;
        ListNode* pre = pre_node;
        ListNode* cur = cur_node;
        ListNode* tmp = nullptr;
        while (last_k) {
            if (!cur) {
                last_head = cur_node;
                final_head = pre_node;
                {
                    ListNode* end_pre = nullptr;
                    ListNode* end_cur = pre;
                    cout<<"end:"<<end_cur->val<<endl;
                    while (end_cur != final_head) {
                        ListNode* end_tmp = end_cur->next;
                        end_cur->next = end_pre;
                        end_pre = end_cur;
                        end_cur = end_tmp;
                    }
                }
                return;
            }
            tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
            --last_k;
        }
        cout<<cnt<<":"<<pre->val<<" "<<cur->val<<" k:"<<k<<endl;
        reverseList(cur_node, cur, k, last_head, final_head);
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* last_head = nullptr;
        ListNode* final_head = nullptr;
        reverseList(nullptr, head, k, last_head, final_head);
        // cout<<head->val<<" "<<last_head->val<<" "<<
        // last_head->next->val<<" "<<final_head->val<<" "<<last_head->next->next->val<<endl;
        head->next = last_head;
        return final_head;
    }
};