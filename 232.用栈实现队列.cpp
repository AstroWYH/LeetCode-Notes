栈 队列

思路：用栈模拟队列行为，一个栈是不行的，需要两个栈。一个用来做输入栈st_in，另一个做输出栈st_out。画图理解。
push()：直接push()到st_in中。
pop()：如果st_out空，则需要先把st_in的内容全搬到st_out。然后正常调记录st_out的top()，并正常调
st_out的pop()；如果st_out本就不为空，则正常执行后面步骤。
peek()：和pop()类似，考虑复用pop()，因为pop()考虑的情况peek()也都需要考虑到。
empty()：st_in和st_out都为空时，则为空。

注：需要熟悉栈、队列数据结构和操作。此两者都没有访问和迭代器iter机制，但是都有push()、pop()等相似操作。
栈：先进后出；队列：先进先出。
注：C++标准库的std::stack底层可以指定是deque(默认)、vector、list来实现，因此其往往不被视为“容器”，
而被视为“容器适配器”"container adapter"。

注：此题两个栈实现队列操作，自己想是比较难想到的。需要画图理解“两个栈一上一下，出口对着”。
注：此题pop()操作也是比较难想到的，尤其是st_out空时，需要一次性将st_in搬运至st_out。

class MyQueue {
private:
    stack<int> st_in;
    stack<int> st_out;
public:
    MyQueue() {

    }

    void push(int x) {
        st_in.push(x);
    }
    
    int pop() {
        if (st_out.empty()) {
            while (!st_in.empty()) {
                st_out.push(st_in.top());
                st_in.pop();
            }
        }
        int res = st_out.top();
        st_out.pop();
        return res;
    }

    int peek() {
        int res = this->pop();
        st_out.push(res);
        return res;
    }

    bool empty() {
        return st_in.empty() && st_out.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */