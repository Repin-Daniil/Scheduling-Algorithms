#include "SchedulerFCFS.h"

namespace scheduler {

Scheduler::Queue SchedulerFCFS::AddProcess(Process new_process) {
  if(new_process.time == 0) {
    return {};
  }

  processes_.push_back(new_process);

  if (!job_queue_.empty()) {
    duration_of_waiting_ += duration_of_waiting_ + processes_[job_queue_.back()].time;
    duration_of_execution_ += last_execution_time_;
  }

  last_execution_time_ += new_process.time;
  duration_of_execution_ += new_process.time;

  average_timeout_ = duration_of_waiting_ / (processes_.size());
  average_runtime_ = duration_of_execution_ / (processes_.size());

  for (unsigned int i = 0; i < new_process.time; ++i) {
    job_queue_.push(new_process.id);
  }

  return job_queue_;
}

void SchedulerFCFS::Reset() {
  ResetQueue(job_queue_);
  processes_.clear();

  average_timeout_ = average_runtime_ = 0;
  duration_of_execution_ = duration_of_waiting_ = last_execution_time_ = 0;
}

} // scheduler