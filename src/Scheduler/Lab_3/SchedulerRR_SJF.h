#pragma once

#include <vector>
#include <utility>
#include <queue>
#include <functional>

#include "../Scheduler.h"

namespace scheduler {

class SchedulerRR_SJF : public Scheduler {
 public:
  using PriorityQueue = std::priority_queue<Process, std::vector<Process>, std::greater<>>;

  SchedulerRR_SJF() : Scheduler(RR_SJF) {
  }

  Queue AddProcess(Process new_process) override;

 private:
  void ResetSpecific() override;

 private:
  PriorityQueue ready_queue_;
};

}  // namespace scheduler
