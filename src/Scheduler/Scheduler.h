#pragma once

#include <queue>
#include "../constants_storage.h"

namespace scheduler {

struct Process {
  unsigned int id;
  unsigned int time;
};

class Scheduler {
 public:
  using Queue = std::queue<Process>;

  Scheduler(Algorithm algorithm) : algorithm_(algorithm) {
  }

  Queue AddProcess(Process process);
  void Reset();

  // Getters
  double GetMiddleTimeout() const noexcept;
  double GetMiddleRuntime() const noexcept;
  unsigned int GetProcessAmount() const noexcept;

 private:
  Algorithm algorithm_;
  Queue job_queue_;

  double middle_timeout_ = 0.0;
  double middle_runtime_ = 0.0;

  unsigned int duration_of_execution_ = 0;
  unsigned int duration_of_waiting_ = 0;
  unsigned int last_execution_time_ = 0;
};

} // namespace scheduler
