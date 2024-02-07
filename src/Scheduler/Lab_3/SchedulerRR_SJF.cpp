#include "SchedulerRR_SJF.h"

namespace scheduler {

Scheduler::Queue SchedulerRR_SJF::AddProcess(Process new_process) {
  if (new_process.time == 0) {
    return job_queue_;
  }

  processes_.push_back(new_process);

  ResetQueues();

  int order = 0;

  for (auto &process : processes_) {
    ready_queue_.push({process.id, process.time, order++});
  }

  int time = 0;
  std::vector<int> current_process_time(processes_.size(), 0);

  while (!ready_queue_.empty()) {
    auto process_id = ready_queue_.top().id;
    job_queue_.push(process_id);

    ++time;

    if (++current_process_time[process_id] < processes_[process_id].time) {
      ready_queue_.push({process_id, processes_[process_id].time, order++});
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

void SchedulerRR_SJF::ResetSpecific() {
  PriorityQueue empty;
  std::swap(ready_queue_, empty);
}

}  // namespace scheduler
