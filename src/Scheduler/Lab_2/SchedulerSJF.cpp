#include <algorithm>
#include "SchedulerSJF.h"

namespace scheduler {

Scheduler::Queue SchedulerSJF::AddProcess(Process new_process) {
  if (new_process.time == 0) {
    return job_queue_;
  }

  processes_.push_back(new_process);

  ResetQueues();

  auto sorted = processes_;
  std::sort(sorted.begin(), sorted.end());

  int time = 0;

  for (auto &process : sorted) {
    for (size_t i = 0; i < process.time; ++i) {
      ++time;
      job_queue_.push(process.id);
    }

    average_timeout_ += time - process.time;
    average_runtime_ += time;
  }

  average_timeout_ /= processes_.size();
  average_runtime_ /= processes_.size();

  return job_queue_;
}

}  // namespace scheduler
