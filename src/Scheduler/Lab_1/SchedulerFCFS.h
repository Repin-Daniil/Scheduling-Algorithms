#pragma once

#include "../../constants_storage.h"
#include "../Scheduler.h"

namespace scheduler {

class SchedulerFCFS : public Scheduler {
 public:
  Queue AddProcess(Process new_process) override;
  void Reset() override;

 private:
  unsigned int duration_of_execution_ = 0;
  unsigned int duration_of_waiting_ = 0;
  unsigned int last_execution_time_ = 0;
};

} // scheduler
