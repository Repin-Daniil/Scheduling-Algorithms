#pragma once

#include "../Scheduler.h"

namespace scheduler {

class SchedulerPSJF : public Scheduler {
 public:
  Queue AddProcess(Process new_process) override;
  void Reset() override;
};

} // scheduler
