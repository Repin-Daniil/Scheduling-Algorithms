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
  using Queue = std::queue<unsigned int>;

  Scheduler(Algorithm algorithm) : algorithm_(algorithm) {
  }

  Queue AddProcess(Process new_process);
  void Reset();

  // Getters
  double GetAverageTimeout() const noexcept;
  double GetAverageRuntime() const noexcept;
  unsigned int GetProcessAmount() const noexcept;
  unsigned int GetProcessTime(unsigned int process_id) const noexcept;

 private:
  void ResetQueue(std::queue<unsigned int>& queue);

 private:
  Algorithm algorithm_;
  std::vector<Process> processes_;
  Queue job_queue_;

  double average_timeout_ = 0.0;
  double average_runtime_ = 0.0;

  // For FCFS
  unsigned int duration_of_execution_ = 0;
  unsigned int duration_of_waiting_ = 0;
  unsigned int last_execution_time_ = 0;

  // FOR RR
  Queue ready_queue_;

  //TODO Тут бы абстрактную фабрику прикрутить
};

} // namespace scheduler
