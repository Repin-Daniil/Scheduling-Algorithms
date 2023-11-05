#include "Scheduler.h"

namespace scheduler {

Scheduler::Queue Scheduler::AddProcess(Process process) {
  if (algorithm_ == FCFS) {
    if (!job_queue_.empty()) {
      duration_of_waiting_ += duration_of_waiting_ + job_queue_.back().time;
      duration_of_execution_ += last_execution_time_;
    }

    last_execution_time_ += process.time;
    duration_of_execution_ += process.time;

    middle_timeout_ = duration_of_waiting_ / (job_queue_.size() + 1.0);
    middle_runtime_ = duration_of_execution_ / (job_queue_.size() + 1.0);

    job_queue_.push(process);
  }

  return job_queue_;
}

double Scheduler::GetMiddleRuntime() const noexcept {
  return middle_runtime_;
}

double Scheduler::GetMiddleTimeout() const noexcept {
  return middle_timeout_;
}

unsigned int Scheduler::GetProcessAmount() const noexcept {
  return job_queue_.size();
}

void Scheduler::Reset() {
  while (!job_queue_.empty()) {
    job_queue_.pop();
  }

  middle_timeout_ = middle_runtime_ = 0;
  duration_of_execution_ = duration_of_waiting_ = last_execution_time_ = 0;
}

} // namespace scheduler
