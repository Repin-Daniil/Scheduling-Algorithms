#include <algorithm>
#include <limits>
#include "SchedulerPSJF.h"

namespace scheduler {

Scheduler::Queue SchedulerPSJF::AddProcess(Process new_process) {
  if(new_process.time == 0) {
    return job_queue_;
  }

  processes_.push_back(new_process);

  average_timeout_ = average_runtime_ = 0;
  ResetQueue(job_queue_);

  std::unordered_map<unsigned int, Process> ready_processes;
  std::vector<unsigned int> remaining_time;

  unsigned int time = 0;
  size_t amount_of_served_processes = 0;

  while (!ready_processes.empty() || amount_of_served_processes < processes_.size()) {
    if (amount_of_served_processes < processes_.size()) {
      ready_processes.emplace(time, processes_[time]);
      remaining_time.push_back(processes_[time].time);
      ++amount_of_served_processes;
    }

    unsigned int process_id = std::distance(remaining_time.begin(), std::min_element(remaining_time.begin(),
                                                                                     remaining_time.end()));

    ++time;
    --remaining_time[process_id];

    if (remaining_time[process_id] == 0) {
      average_timeout_ += time - processes_[process_id].time;
      average_runtime_ += time;

      ready_processes.erase(process_id);
      remaining_time[process_id] = std::numeric_limits<unsigned int>::max();
    }

    job_queue_.push(process_id);
  }

  average_timeout_ /= processes_.size();
  average_runtime_ /= processes_.size();

  return job_queue_;
}

void SchedulerPSJF::Reset() {
  ResetQueue(job_queue_);
  processes_.clear();

  average_timeout_ = average_runtime_ = 0;
}

} // namespace scheduler
