```cpp
#ifndef HEADER
#define HEADER

#include <deque>
#include <functional>
#include <mutex>
#include <pthread.h>
#include <vector>

namespace mp {
typedef std::function<FSP_STATUS()> StatusDispatchFunction;
typedef std::function<void()> VoidDispatchFunction;

class JobDispatcher {
public:
  JobDispatcher();

  ~JobDispatcher();

  JobDispatcher(const JobDispatcher &) = delete;

  JobDispatcher &operator=(JobDispatcher) = delete;

  FSP_STATUS Run(StatusDispatchFunction func);

  void ClearJobs();

  void WaitUntilDone();
  void RunWithoutWaiting(VoidDispatchFunction func);

  bool IsCurrentThread();

  void SelfDestruct();

private:
  static void *ThreadBody(void *instance);

  void ThreadBody();

  using Job = std::function<void(void)>;

  Job GetJob();
  inline void CheckComplete();

  void PutJob(Job job);

  std::mutex mutex_;
  // Used to wait for a job's completion.
  bool is_complete_ = true;
  std::condition_variable job_done_cv_;
  std::condition_variable jobs_complete_cv_;
  pthread_t thread_id_;

  std::deque<Job> jobs_;
  std::condition_variable has_jobs_cv_;

  bool self_destruct_ = false;
};
} // namespace mp

#endif // HEADER

#include "JobDispatcher.h"
#include <port/logger.h>


using namespace mp;

static void SetThreadName(const char *name) {
  char thread_name[16]; // Linux requires names (with nul) fit in 16 chars
  strncpy(thread_name, name, sizeof(thread_name));
  thread_name[sizeof(thread_name) - 1] = '\0';
  int res = pthread_setname_np(pthread_self(), thread_name);
  FSP_CHECK_LOG(res != 0, "Can't set pthread names: name: \"%s\", error:%d",
                name, res);
}

mp::JobDispatcher::JobDispatcher() {
  FSP_CHECK_EQ(pthread_create(&thread_id_, nullptr, ThreadBody, this), 0);
}

mp::JobDispatcher::~JobDispatcher() {
  if (IsCurrentThread()) {
    FSP_CHECK(self_destruct_);
    FSP_CHECK_EQ(pthread_detach(thread_id_), 0);
  } else {
    // Give an invalid job to signal termination.
    PutJob({});
    FSP_CHECK_EQ(pthread_join(thread_id_, nullptr), 0);
  }
}

void mp::JobDispatcher::SelfDestruct() {
  self_destruct_ = true;
  // Give an invalid job to signal termination.
  PutJob({});
}

mp::JobDispatcher::Job mp::JobDispatcher::GetJob() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (jobs_.empty()) {
    has_jobs_cv_.wait(lock);
  }
  Job job = std::move(jobs_.front());
  jobs_.pop_front();
  return job;
}

void mp::JobDispatcher::PutJob(Job job) {
  std::lock_guard<std::mutex> lock(mutex_);
  is_complete_ = false;
  jobs_.push_back(std::move(job));
  has_jobs_cv_.notify_all();
}

void *mp::JobDispatcher::ThreadBody(void *instance) {
  JobDispatcher *thread = static_cast<JobDispatcher *>(instance);
  thread->ThreadBody();
  return nullptr;
}

void mp::JobDispatcher::ThreadBody() {
  SetThreadName("JobDispatcher");
  while (true) {
    Job job = GetJob();
    if (!job) {
      CheckComplete();
      FSP_LOGW("No more jobs.");
      break;
    }
    job();
    CheckComplete();
  }
  if (self_destruct_) {
    delete this;
  }
}

FSP_STATUS mp::JobDispatcher::Run(StatusDispatchFunction func) {
  FSP_CHECK(func);
  if (IsCurrentThread()) {
    return func();
  }
  bool done = false;
  FSP_STATUS status;
  PutJob([this, func, &done, &status]() {
    status = func();
    std::unique_lock<std::mutex> lock(mutex_);
    done = true;
    job_done_cv_.notify_all();
  });

  std::unique_lock<std::mutex> lock(mutex_);
  while (!done) {
    job_done_cv_.wait(lock);
  }
  return status;
}

void mp::JobDispatcher::RunWithoutWaiting(VoidDispatchFunction func) {
  FSP_CHECK(func);
  PutJob(std::move(func));
}

bool mp::JobDispatcher::IsCurrentThread() {
  return pthread_equal(thread_id_, pthread_self());
}

void JobDispatcher::WaitUntilDone() {
  std::unique_lock<std::mutex> lock(mutex_);
  while (!is_complete_) {
    jobs_complete_cv_.wait(lock);
  }
}

void JobDispatcher::CheckComplete() {
  std::unique_lock<std::mutex> lock(mutex_);

  if (jobs_.empty()) {
    is_complete_ = true;
    jobs_complete_cv_.notify_all();
  }
}

void JobDispatcher::ClearJobs() {
  std::deque<Job> q_jobs;
  {
    std::lock_guard<std::mutex> _lock(mutex_);
    FSP_LOGW("clear jobs %d", jobs_.size());
    q_jobs.swap(jobs_);
  }
  auto func = [](std::deque<Job> jobs) { jobs.clear(); };
  auto func_bind = std::bind(func, std::move(q_jobs));
  PutJob(func_bind);
}
```

