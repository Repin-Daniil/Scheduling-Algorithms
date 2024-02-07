#pragma once

#include <memory>
#include <utility>

#include "Scheduler.h"
#include "Lab_1/SchedulerFCFS.h"
#include "Lab_2/SchedulerRR.h"
#include "Lab_2/SchedulerSJF.h"
#include "Lab_3/SchedulerPSJF.h"
#include "Lab_3/SchedulerRR_SJF.h"

namespace scheduler {

class SchedulerFactory {
 public:
  static std::unique_ptr<Scheduler> CreateScheduler(Algorithm algo) {
    std::unique_ptr<Scheduler> scheduler;

    if (algo == Algorithm::FCFS) {
      scheduler = std::make_unique<scheduler::SchedulerFCFS>();
    } else if (algo == Algorithm::RR) {
      scheduler = std::make_unique<scheduler::SchedulerRR>();
    } else if (algo == Algorithm::SJF) {
      scheduler = std::make_unique<scheduler::SchedulerSJF>();
    } else if (algo == Algorithm::PSJF) {
      scheduler = std::make_unique<scheduler::SchedulerPSJF>();
    } else if (algo == Algorithm::RR_SJF) {
      scheduler = std::make_unique<scheduler::SchedulerRR_SJF>();
    }

    return std::move(scheduler);
  }
};

}  // namespace scheduler
