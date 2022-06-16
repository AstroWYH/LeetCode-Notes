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

思路：此题是很好的链表题，从链表节点LinkedNode的数据结构内部设计，到外部封装大链表MyLinkedList的
成员函数和成员变量设计，回顾可以帮助很好的理解链表。

注：LinkedNode是自己定义的结构体（LinkedNode），手写一遍帮助记忆；
注：采用虚拟头节点m_dummy_node可以很方便地帮助理解和完成整个设计过程，因为如果没有m_dummy_node的话，
那么构造的时候就会莫名其妙多出一个val=0的节点，仅从这一点上就不方便很多。
注：m_size记录链表的长度，很有必要，加入节点时++删除节点时--，能在index判断是否大于tail时起到作用；

注：cur是比较讲究的，实现get()时，那么cur=m_dummy_node->next，因为需要index=0时，cur刚好遍历到该
节点上（画图理解），然后返回该节点的val；而实现addAtTail()、addAtIndex()、deleteAtIndex()等时，
cur=m_dummy_node即可，因为需要index=0时，cur刚好遍历到index指向节点的上一节点（画图理解），此时才
方便进行尾部插入、index节点前插入、index节点删除等操作，这一点很关键。

注：if(index...)的判断也很关键，index<0是直接不考虑的，index=0表示head头节点；index=m_size则表示
尾节点指向的nullptr（可以理解为没有节点），所以一般遍历index>(m_size-1)或index>=m_size，就表示
index指向nullptr没有节点了；有时判断为index>m_size，那说明此时把index指向nullptr的情况包含考虑了。

class MyLinkedList {
private:
    struct LinkedNode
    {
        int val;
        LinkedNode* next;
        LinkedNode():val(0), next(nullptr) {}
        LinkedNode(int val):val(val), next(nullptr) {}
        LinkedNode(int val, LinkedNode* next):val(val), next(next) {}
    };

    LinkedNode* m_dummy_node = nullptr;
    int m_size = 0;
public:
    MyLinkedList() {
        m_dummy_node = new LinkedNode();
    }

    int get(int index) {
        if (index > (m_size - 1) || index < 0) {
            return -1;
        }
        LinkedNode* cur = m_dummy_node->next;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val) {
        LinkedNode* new_node = new LinkedNode(val);
        new_node->next = m_dummy_node->next;
        m_dummy_node->next = new_node;
        m_size++;
    }

    void addAtTail(int val) {
        LinkedNode* new_node = new LinkedNode(val);
        LinkedNode* cur = m_dummy_node;
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = new_node;
        m_size++;
    }

    void addAtIndex(int index, int val) {
        if (index > m_size) return;
        LinkedNode* new_node = new LinkedNode(val);
        LinkedNode* cur = m_dummy_node;
        while (index--) {
            cur = cur->next;
        }
        new_node->next = cur->next;
        cur->next = new_node;
        m_size++;
    }

    void deleteAtIndex(int index) {
        if (index >= m_size || index < 0) return;
        LinkedNode* cur = m_dummy_node;
        while (index--) {
            cur = cur->next;
        }
        LinkedNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        m_size--;
    }

    void printLinkedList() {
        LinkedNode* cur = m_dummy_node;
        while (cur->next != nullptr) {
            std::cout << cur->next->val << " ";
            cur = cur->next;
        }
        std::cout << endl;
    }
};

以下自己刚开始写的版本，存在不少问题。
问题1：构造出来的node已经自带一个val=0的node了。

class MyLinkedList {
private:
    ListNode* m_head = nullptr;
public:
    MyLinkedList() {
        m_head = new ListNode();
    }

    int get(int index) {
        ListNode* cur = m_head;
        int idx = 0;
        while (cur != nullptr && idx != index) {
            cur = cur->next;
            idx++;
        }
        return cur == nullptr ? -1 : cur->val;
    }

    void addAtHead(int val) {
        ListNode* add_head_node = new ListNode();
        add_head_node->val = val;
        add_head_node->next = m_head;
        m_head = add_head_node;
    }

    void addAtTail(int val) {
        ListNode* cur = m_head;
        while (cur != nullptr) {
            cur = cur->next;
        }
        ListNode* add_tail_node = new ListNode();
        add_tail_node->val = val;
        cur = add_tail_node;
    }

    void addAtIndex(int index, int val) {
        if (index <= 0) addAtHead(val);
        ListNode* cur = m_head;
        int idx = 0;
        while (cur != nullptr && (idx + 1) != index) {
            cur = cur->next;
            idx++;
        }
        ListNode* add_idx_node = new ListNode();
        add_idx_node->val = val;
        if (cur != nullptr) {
            add_idx_node->next = cur->next;
            cur->next = add_idx_node;
        } else {
            addAtTail(val);
        }
    }

    void deleteAtIndex(int index) {
        if (index < 0) return;
        if (index == 0 && m_head != nullptr) {
            ListNode* tmp = m_head;
            m_head = m_head->next;
            delete tmp;
        } 
        ListNode* cur = m_head;
        int idx = 0;
        while (cur != nullptr && (idx + 1) != index) {
            cur = cur->next;
            idx++;
        }
        if (cur->next != nullptr) {
            ListNode* tmp = cur->next;
            cur->next = cur->next->next;
            delete tmp;
        }
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */