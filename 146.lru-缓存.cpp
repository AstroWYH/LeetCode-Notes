哈希map+双向链表

思路：LRU（最近最少使用）缓存策略经典题，哈希map主要是用来快速查询定位，双向链表用来“逐出最久未使用的关键字”。

注：哈希map的使用，一是“用于记录，毕竟key、val”；二是O(1)的find()复杂度，可以满足此题要求的“随机访问”。
记住unordered_map的两个特点。
注：此题双向链表和哈希map，从node上来看是一一对应的，从key上来看也是一一对应的。
注：此题双向链表内数据是key、val，不仅仅是val。且key和哈希map的key是对应的。目的就是当get(key)双向链表时，
得用这个key也去map里find(key)，就能“在O(1)复杂度内达到查询链表的目的”。
注：双向链表需要考虑“虚拟头、尾节点：dummy_head、dummy_tail”。
注：双向链表实际可以用std::list做，自己实现是加分项。可以注意此题双向链表的具体实现，比如addToHead()，考虑
在虚拟头节点dummy_head后插入，其实要考虑的就是4个指针的指向，插入node的前后、dummy_head的后、dummy_head->next
的前，这点想清楚。
注：此题的size、capacity的用法也值得学习。capacity构造时就固定，size则动态变化，但不能超过capacity。
注：get()、put()是此题的解题关键，哈希map+双向链表也在此体现，“逐出最久未使用的关键字”关键在于每次这俩操作后，
都将node移到head去。
注：get()、put()都是O(1)的复杂度，因为查询过程是O(1)——“哈希map”，插入头部也是O(1)——“双向链表”。

struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int key, int value): key(key), value(value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* dummy_head;
    DLinkedNode* dummy_tail;
    int size;
    int capacity;

public:
    LRUCache(int capacity): capacity(capacity), size(0) {
        // 使用伪头部和伪尾部节点
        dummy_head = new DLinkedNode();
        dummy_tail = new DLinkedNode();
        dummy_head->next = dummy_tail;
        dummy_tail->prev = dummy_head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = dummy_head;
        node->next = dummy_head->next;
        dummy_head->next->prev = node;
        dummy_head->next = node;
    }
    
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = dummy_tail->prev;
        removeNode(node);
        return node;
    }
};
