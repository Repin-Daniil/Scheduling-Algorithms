#pragma once

#include <queue>
#include "../constants_storage.h"

namespace scheduler {

struct Process {
  unsigned int id;
  unsigned int time;
  unsigned int entry_time;

  bool operator<(const Process &other) const {
    if (time == other.time) {
      return (entry_time < other.entry_time);
    }

    return time < other.time;
  }

  bool operator>(const Process &other) const {
    if (time == other.time) {
      return (entry_time > other.entry_time);
    }

    return time > other.time;
  }
};

class Scheduler {
 public:
  using Queue = std::queue<unsigned int>;

  virtual Queue AddProcess(Process new_process) = 0;
  virtual void Reset() = 0;

  // Getters
  virtual double GetAverageTimeout() const noexcept;
  virtual double GetAverageRuntime() const noexcept;
  virtual unsigned int GetProcessAmount() const noexcept;
  virtual unsigned int GetProcessTime(unsigned int process_id) const noexcept;

 protected:
  virtual void ResetQueue(std::queue<unsigned int> &queue);

 protected:
  std::vector<Process> processes_;
  Queue job_queue_;

  double average_timeout_ = 0.0;
  double average_runtime_ = 0.0;
};

} // namespace scheduler
