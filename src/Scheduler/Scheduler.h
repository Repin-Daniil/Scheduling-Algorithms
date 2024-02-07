#pragma once

#include <queue>
#include <stdexcept>
#include <vector>
#include <utility>

#include "../constants_storage.h"

namespace scheduler {

struct Process {
  int id;
  int time;
  int entry_time;

  bool operator<(const Process &other) const;
  bool operator>(const Process &other) const;
};

class Scheduler {
 public:
  using Queue = std::queue<int>;

  explicit Scheduler(Algorithm algo) : algorithm_(algo) {
  }

  virtual ~Scheduler() = default;

  void Reset();
  virtual Queue AddProcess(Process new_process) = 0;

  [[nodiscard]] virtual double GetAverageTimeout() const noexcept;
  [[nodiscard]] virtual double GetAverageRuntime() const noexcept;
  [[nodiscard]] virtual int GetProcessAmount() const noexcept;
  [[nodiscard]] virtual int GetProcessTime(int process_id) const;
  [[nodiscard]] virtual std::vector<Process> GetProcesses() const noexcept;
  [[nodiscard]] virtual Queue GetJobQueue() const noexcept;
  [[nodiscard]] virtual Algorithm GetAlgorithm() const noexcept;

 protected:
  virtual void ResetQueues();
  virtual void ResetSpecific();

 protected:
  const Algorithm algorithm_;
  std::vector<Process> processes_;
  Queue job_queue_;

  double average_timeout_ = 0.0;
  double average_runtime_ = 0.0;
};

}  // namespace scheduler
