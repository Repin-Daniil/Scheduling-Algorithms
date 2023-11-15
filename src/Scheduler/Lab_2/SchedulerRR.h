#pragma once

#include "../Scheduler.h"

namespace scheduler {

class SchedulerRR : public Scheduler {
 public:
  Queue AddProcess(Process new_process) override;
  void Reset() override;

 private:
  Queue ready_queue_;
};

} // scheduler
