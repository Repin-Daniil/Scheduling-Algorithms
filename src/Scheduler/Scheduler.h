#pragma once

#include <queue>
#include "../constants_storage.h"

namespace scheduler {

struct Process {
  unsigned int id;
  unsigned int time;
  unsigned int entry_time;

  bool operator<(const Process &other) const;
  bool operator>(const Process &other) const;
};

class Scheduler {
 public:
  using Queue = std::queue<unsigned int>;

  Scheduler(Algorithm algo) : algorithm_(algo) {
  }

  virtual Queue AddProcess(Process new_process) = 0;
  virtual void Reset() = 0;

  // Getters
  virtual double GetAverageTimeout() const noexcept;
  virtual double GetAverageRuntime() const noexcept;
  virtual unsigned int GetProcessAmount() const noexcept;
  virtual unsigned int GetProcessTime(unsigned int process_id) const;
  virtual std::vector<Process> GetProcesses() const noexcept;
  virtual Queue GetJobQueue() const noexcept;
  virtual Algorithm GetAlgorithm() const noexcept;

 protected:
  virtual void ResetQueue(std::queue<unsigned int> &queue);

 protected:
  const Algorithm algorithm_;
  std::vector<Process> processes_;
  Queue job_queue_;

  double average_timeout_ = 0.0;
  double average_runtime_ = 0.0;
};

} // namespace scheduler
