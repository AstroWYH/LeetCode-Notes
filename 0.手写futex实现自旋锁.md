- futex（fast userspace mutex）是一种实现互斥锁（mutex）的同步原语，旨在提高用户空间多线程应用程序的性能。
- 传统的互斥锁（mutex）实现通常需要在内核态和用户态之间进行频繁的上下文切换，这种上下文切换的开销可能会导致性能瓶颈。为了避免这种开销，futex 将互斥锁的实现分为两个部分：一个用户空间部分和一个内核空间部分。只有在互斥锁的状态发生变化时，才需要进行内核态和用户态之间的切换。
- futex 还支持等待队列，当一个线程需要等待一个互斥锁时，它可以将自己添加到等待队列中。当其他线程释放锁时，它们可以唤醒等待队列中的线程。
- futex 是一种非常高效的同步原语，通常用于高并发的多线程应用程序。在 Linux 内核中，futex 被广泛使用，并且成为了 POSIX 线程标准的一部分。

- **传统的互斥锁实现通常使用了内核态提供的系统调用，例如pthread_mutex_lock()，这些系统调用需要在用户态和内核态之间进行频繁的上下文切换。具体来说，当一个线程调用pthread_mutex_lock()获取锁时，如果该锁已被其他线程占用，那么该线程会进入等待状态并切换到内核态，等待内核将其唤醒。当该锁被释放时，内核会重新调度等待该锁的线程之一，并将其唤醒，使其重新进入用户态并继续执行。这样的频繁上下文切换会带来较大的系统开销。而futex则是一种用户态的锁，避免了频繁的上下文切换，从而提高了锁的性能。**

```cpp
#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <atomic>

class SpinLock {
public:
    SpinLock() : flag(false) {}

    void lock() {
        while (true) {
            bool expected = false;
            // 尝试将 flag 原子变量从 false 置为 true
            if (flag.compare_exchange_strong(expected, true)) {
                return; // 成功获取锁
            }
            // 获取锁失败，等待
            syscall(SYS_futex, &flag, FUTEX_WAIT, 1, nullptr, nullptr, 0);
        }
    }

    void unlock() {
        // 释放锁，将 flag 原子变量置为 false
        flag.store(false);
        // 唤醒等待该锁的线程
        syscall(SYS_futex, &flag, FUTEX_WAKE, 1, nullptr, nullptr, 0);
    }

private:
    std::atomic<bool> flag; // 原子变量用于实现自旋锁
};

int main() {
    SpinLock lock; // 创建自旋锁
    int count = 0; // 共享变量

    for (int i = 0; i < 10; ++i) {
        // 创建 10 个线程并发修改共享变量
        std::thread([&]{
            for (int j = 0; j < 100000; ++j) { // 每个线程累加 100000 次
                lock.lock(); // 获取锁
                ++count; // 修改共享变量
                lock.unlock(); // 释放锁
            }
        }).detach(); // 分离线程，使得线程结束时自动回收资源
    }

    sleep(1); // 等待 1 秒，等待线程执行完毕
    std::cout << "count = " << count << std::endl; // 输出共享变量的值

    return 0;
}
```

这段代码实现了一个自旋锁，并用该锁保护了一个共享变量`count`的并发访问。其中，`SpinLock`类实现了自旋锁，通过`flag`原子变量的状态实现自旋等待，通过系统调用`syscall`函数实现了对`flag`原子变量的操作。`main`函数创建了 10 个线程，并发修改`count`共享变量，每个线程累加`count`的值 100000 次。`sleep(1)`语句等待所有线程执行完毕，然后输出`count`的值。