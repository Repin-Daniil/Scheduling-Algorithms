#pragma once

#include <unordered_map>
#include <vector>

#include "../Scheduler.h"

namespace scheduler {

class SchedulerPSJF : public Scheduler {
 public:
  SchedulerPSJF() : Scheduler(PSJF) {
  }

  Queue AddProcess(Process new_process) override;
};

}  // namespace scheduler
