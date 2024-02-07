#include <algorithm>
#include <limits>
#include "SchedulerPSJF.h"

namespace scheduler {

Scheduler::Queue SchedulerPSJF::AddProcess(Process new_process) {
  if (new_process.time == 0) {
    return job_queue_;
  }

  processes_.push_back(new_process);

  ResetQueues();

  std::unordered_map<int, Process> ready_processes;
  std::vector<int> remaining_time;

  int time = 0;
  int amount_of_served_processes = 0;

  while (!ready_processes.empty() || amount_of_served_processes < processes_.size()) {
    if (amount_of_served_processes < processes_.size()) {
      ready_processes.emplace(time, processes_[time]);
      remaining_time.push_back(processes_[time].time);
      ++amount_of_served_processes;
    }

    int process_id = std::distance(remaining_time.begin(), std::min_element(remaining_time.begin(),
                                                                            remaining_time.end()));

    ++time;
    --remaining_time[process_id];

    if (remaining_time[process_id] == 0) {
      average_timeout_ += time - processes_[process_id].time;
      average_runtime_ += time;

      ready_processes.erase(process_id);
      remaining_time[process_id] = std::numeric_limits<int>::max();
    }

    job_queue_.push(process_id);
  }

  average_timeout_ /= processes_.size();
  average_runtime_ /= processes_.size();

  return job_queue_;
}

}  // namespace scheduler
