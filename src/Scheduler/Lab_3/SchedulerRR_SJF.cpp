#include "SchedulerRR_SJF.h"

namespace scheduler {

Scheduler::Queue SchedulerRR_SJF::AddProcess(Process new_process) {
  processes_.push_back(new_process);

  average_timeout_ = average_runtime_ = 0;
  ResetPriorityQueue(ready_queue_);
  ResetQueue(job_queue_);

  unsigned int order = 0;

  for (auto &process : processes_) {
    ready_queue_.push({process.id, process.time, order++});
  }

  unsigned int time = 0;
  std::vector<unsigned int> current_process_time(processes_.size(), 0);

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

void SchedulerRR_SJF::Reset() {
  ResetQueue(job_queue_);
  ResetPriorityQueue(ready_queue_);
  processes_.clear();

  average_timeout_ = average_runtime_ = 0;
}

void SchedulerRR_SJF::ResetPriorityQueue(SchedulerRR_SJF::PriorityQueue &queue) {
  PriorityQueue empty;
  std::swap(queue, empty);
}

} // namespace scheduler
