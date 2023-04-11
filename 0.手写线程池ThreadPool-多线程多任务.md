ThreadPool.h

```cpp
#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <atomic>
#include <future>
#include <queue>
#include <vector>

// #include <condition_variable>
// #include <thread>
// #include <functional>
#include <stdexcept>

namespace std {
// 线程池最大容量,应尽量设小一点
#define THREADPOOL_MAX_NUM 16
// 线程池是否可以自动增长(如果需要,且不超过THREADPOOL_MAX_NUM)
// #define THREADPOOL_AUTO_GROW

// 线程池,可以提交变参函数或拉姆达表达式的匿名函数执行,可以获取执行返回值
// 不直接支持类成员函数, 支持类静态成员函数或全局函数,Opteron()函数等
class threadpool {
  unsigned short init_size_;     // 初始化线程数量
  using Task = function<void()>; // 定义类型
  vector<thread> pool_;          // 线程池
  queue<Task> tasks_;            // 任务队列
  mutex lock_;                   // 任务队列同步锁
#ifdef THREADPOOL_AUTO_GROW
  mutex lock_grow_;             // 线程池增长同步锁
#endif                          // !THREADPOOL_AUTO_GROW
  condition_variable task_cv_;  // 条件阻塞
  atomic<bool> run_{true};      // 线程池是否执行
  atomic<int> idle_tid_num_{0}; // 空闲线程数量

public:
  inline threadpool(unsigned short size = 4) {
    init_size_ = size;
    addThread(size);
  }
  inline ~threadpool() {
    run_ = false;
    task_cv_.notify_all(); // 唤醒所有线程执行
    for (thread &thread : pool_) {
      // thread.detach(); // 让线程“自生自灭”
      if (thread.joinable())
        thread.join(); // 等待任务结束，前提：线程一定会执行完
    }
  }

public:
  // 提交一个任务
  // 调用.get()获取返回值会等待任务执行完,获取返回值
  // 有两种方法可以实现调用类成员
  // 一种是使用bind：.commit(std::bind(&Dog::sayHello, &dog));
  // 一种是用mem_fn：.commit(std::mem_fn(&Dog::sayHello), this)
  template <class F, class... Args>
  auto commit(F &&f, Args &&...args) -> future<decltype(f(args...))> {
    if (!run_) // stoped ??
      throw runtime_error("commit on ThreadPool is stopped.");

    using RetType = decltype(f(args...));
    // typename std::result_of<F(Args...)>::type, 函数f的返回值类型
    auto task = make_shared<packaged_task<RetType()>>(bind(
        forward<F>(f), forward<Args>(args)...)); // 把函数入口及参数,打包(绑定)
    future<RetType> future = task->get_future();
    { // 添加任务到队列
      lock_guard<mutex> lock{lock_};
      // 对当前块的语句加锁lock_guard是mutex的stack封装类，构造的时候lock(),
      // 析构的时候 unlock()
      tasks_.emplace([task]() { // push(Task{...}) 放到队列后面
        (*task)();
      });
    }
#ifdef THREADPOOL_AUTO_GROW
    if (idle_tid_num_ < 1 && pool_.size() < THREADPOOL_MAX_NUM)
      addThread(1);
#endif                     // !THREADPOOL_AUTO_GROW
    task_cv_.notify_one(); // 唤醒一个线程执行

    return future;
  }
  // 提交一个无参任务, 且无返回值
  template <class F> void commit2(F &&task) {
    if (!run_)
      return;
    {
      lock_guard<mutex> lock{lock_};
      tasks_.emplace(std::forward<F>(task));
    }
#ifdef THREADPOOL_AUTO_GROW
    if (idle_tid_num_ < 1 && pool_.size() < THREADPOOL_MAX_NUM)
      addThread(1);
#endif // !THREADPOOL_AUTO_GROW
    task_cv_.notify_one();
  }
  // 空闲线程数量
  int idlCount() { return idle_tid_num_; }
  // 线程数量
  int thrCount() { return pool_.size(); }

#ifndef THREADPOOL_AUTO_GROW
private:
#endif // !THREADPOOL_AUTO_GROW
       // 添加指定数量的线程
  void addThread(unsigned short size) {
#ifdef THREADPOOL_AUTO_GROW
    if (!run_) // stoped ??
      throw runtime_error("Grow on ThreadPool is stopped.");
    unique_lock<mutex> lock_grow{lock_grow_}; // 自动增长锁
#endif                                        // !THREADPOOL_AUTO_GROW
    for (; pool_.size() < THREADPOOL_MAX_NUM && size > 0; --size) {
      // 增加线程数量,但不超过 预定义数量 THREADPOOL_MAX_NUM
      pool_.emplace_back([this] { // 工作线程函数
        while (true) // 防止 run_==false 时立即结束, 此时任务队列可能不为空
        {
          Task task; // 获取一个待执行的 task
          {
            // unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()
            unique_lock<mutex> lock{lock_};
            task_cv_.wait(lock, [this] { // wait 直到有 task, 或需要停止
              return !run_ || !tasks_.empty();
            });
            if (!run_ && tasks_.empty())
              return;
            idle_tid_num_--;
            task = move(tasks_.front()); // 按先进先出从队列取一个 task
            tasks_.pop();
          }
          task(); // 执行任务
#ifdef THREADPOOL_AUTO_GROW
          if (idle_tid_num_ > 0 && pool_.size() > init_size_)
            return;
            // 支持自动释放空闲线程,避免峰值过后大量空闲线程
#endif // !THREADPOOL_AUTO_GROW
          {
            unique_lock<mutex> lock{lock_};
            idle_tid_num_++;
          }
        }
      });
      {
        unique_lock<mutex> lock{lock_};
        idle_tid_num_++;
      }
    }
  }
};

} // namespace std

#endif
```

main.cpp

```cpp
#include "threadpool.h"
#include <iostream>
#include <windows.h>

void fun1(int slp) {
  printf("  hello, fun1 !  %d\n", std::this_thread::get_id());
  if (slp > 0) {
    printf(" ======= fun1 sleep %d  =========  tid:%d\n", slp,
           std::this_thread::get_id());
    std::this_thread::sleep_for(std::chrono::milliseconds(slp));
    // Sleep(slp );
  }
}

struct gfun {
  int operator()(int n) {
    printf("%d  hello, gfun !  tid:%d\n", n, std::this_thread::get_id());
    return 42;
  }
};

class A { // 函数必须是 static 的才能使用线程池
public:
  static int Afun(int n = 0) {
    std::cout << n << "  hello, Afun !  tid:" << std::this_thread::get_id()
              << std::endl;
    return n;
  }

  static std::string Bfun(int n, std::string str, char c) {
    std::cout << n << "  hello, Bfun !  " << str.c_str() << "  " << (int)c
              << "  tid:" << std::this_thread::get_id() << std::endl;
    return str;
  }
};

int main() try {
  std::threadpool executor{50};
  A a;
  std::future<void> ff = executor.commit(fun1, 0);
  std::future<int> fg = executor.commit(gfun{}, 0);
  std::future<int> gg = executor.commit(a.Afun, 9999);
  // IDE提示错误,但可以编译运行
  std::future<std::string> gh =
      executor.commit(A::Bfun, 9998, "mult args", 123);
  std::future<std::string> fh = executor.commit([]() -> std::string {
    std::cout << "hello, fh! tid:" << std::this_thread::get_id() << std::endl;
    return "hello, fh ret!";
  });

  std::cout << " =======  sleep  ========= tid:" << std::this_thread::get_id()
            << std::endl;
  std::this_thread::sleep_for(std::chrono::microseconds(900));

  for (int i = 0; i < 50; i++) {
    executor.commit(fun1, i * 100);
  }
  std::cout << " =======  commit all  ========= tid:"
            << std::this_thread::get_id() << " idlsize=" << executor.idlCount()
            << std::endl;

  std::cout << " =======  sleep  ========= tid:" << std::this_thread::get_id()
            << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));

  ff.get(); // 调用.get()获取返回值会等待线程执行完,获取返回值
  std::cout << fg.get() << "  " << fh.get().c_str()
            << "  tid:" << std::this_thread::get_id() << std::endl;

  std::cout << " =======  sleep  ========= tid:" << std::this_thread::get_id()
            << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::cout << " =======  fun1,55  ========= tid:" << std::this_thread::get_id()
            << std::endl;
  executor.commit(fun1, 55).get(); // 调用.get()获取返回值会等待线程执行完

  std::cout << "end... tid:" << std::this_thread::get_id() << std::endl;

  std::threadpool pool(4);
  std::vector<std::future<int>> results;

  for (int i = 0; i < 8; ++i) {
    results.emplace_back(pool.commit([i] {
      std::cout << "hello " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "world " << i << std::endl;
      return i * i;
    }));
  }
  std::cout << " =======  commit all2  ========= tid:"
            << std::this_thread::get_id() << std::endl;

  for (auto &&result : results)
    std::cout << result.get() << ' ';
  std::cout << std::endl;
  return 0;
} catch (std::exception &e) {
  std::cout << "some unhappy happened...  tid:" << std::this_thread::get_id()
            << e.what() << std::endl;
}
```

