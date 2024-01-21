#pragma once

#include "../Scheduler.h"

namespace scheduler {

class SchedulerPSJF : public Scheduler {
 public:
  SchedulerPSJF() : Scheduler(PSJF) {
  }

  Queue AddProcess(Process new_process) override;
  void Reset() override;
};

} // scheduler
