#include "SchedulerRR.h"

namespace scheduler {

Scheduler::Queue SchedulerRR::AddProcess(Process new_process) {
  if (new_process.time == 0) {
    return job_queue_;
  }

  processes_.push_back(new_process);

  ResetQueues();

  for (auto &process : processes_) {
    ready_queue_.push(process.id);
  }

  int time = 0;
  std::vector<int> current_process_time(processes_.size(), 0);

  while (!ready_queue_.empty()) {
    ++time;
    auto process_id = ready_queue_.front();
    job_queue_.push(process_id);

    if (++current_process_time[process_id] < processes_[process_id].time) {
      ready_queue_.push(process_id);
    } else if (current_process_time[process_id] == processes_[process_id].time) {
      average_timeout_ += time - current_process_time[process_id];
      average_runtime_ += time;
    }

    ready_queue_.pop();
  }

  average_timeout_ /= processes_.size();
  average_runtime_ /= processes_.size();

  return job_queue_;
}

void SchedulerRR::ResetSpecific() {
  std::queue<int> empty;
  std::swap(ready_queue_, empty);
}

}  // namespace scheduler
