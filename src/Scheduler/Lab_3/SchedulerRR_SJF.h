#pragma once

#include "../Scheduler.h"

namespace scheduler {

class SchedulerRR_SJF : public Scheduler {
 public:
  using PriorityQueue = std::priority_queue<Process, std::vector<Process>, std::greater<>>;

  Queue AddProcess(Process new_process) override;
  void Reset() override;

 private:
  void ResetPriorityQueue(PriorityQueue &queue);

 private:
  PriorityQueue ready_queue_;
};

} // scheduler
