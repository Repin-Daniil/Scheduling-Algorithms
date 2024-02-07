#pragma once

#include "../Scheduler.h"

namespace scheduler {

class SchedulerSJF : public Scheduler {
 public:
  SchedulerSJF() : Scheduler(SJF) {
  }

  Queue AddProcess(Process new_process) override;
};

}  // namespace scheduler
