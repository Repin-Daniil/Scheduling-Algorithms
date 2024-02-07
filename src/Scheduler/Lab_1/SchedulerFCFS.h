#pragma once

#include <queue>
#include <utility>

#include "../../constants_storage.h"
#include "../Scheduler.h"

namespace scheduler {

class SchedulerFCFS : public Scheduler {
 public:
  SchedulerFCFS() : Scheduler(FCFS) {
  }

  Queue AddProcess(Process new_process) override;

 private:
  void ResetSpecific() override;

 private:
  int duration_of_execution_ = 0;
  int duration_of_waiting_ = 0;
  int last_execution_time_ = 0;
};

}  // namespace scheduler
