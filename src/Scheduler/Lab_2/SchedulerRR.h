#pragma once

#include <vector>
#include <queue>
#include <utility>

#include "../Scheduler.h"

namespace scheduler {

class SchedulerRR : public Scheduler {
 public:
  SchedulerRR() : Scheduler(RR) {
  }

  Queue AddProcess(Process new_process) override;

 private:
  void ResetSpecific() override;

 private:
  Queue ready_queue_;
};

}  // namespace scheduler
