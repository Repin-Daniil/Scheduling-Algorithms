#include <iostream>
#include "Application/Application.h"
#include "Scheduler/Lab_1/SchedulerFCFS.h"
#include "Scheduler/Lab_2/SchedulerRR.h"

int main() {
  try {
    auto algo = Algorithm::RR;
    std::shared_ptr<scheduler::Scheduler> scheduler;

    if (algo == Algorithm::FCFS) {
      scheduler = std::make_shared<scheduler::SchedulerFCFS>();
    } else if (algo == Algorithm::RR) {
      scheduler = std::make_shared<scheduler::SchedulerRR>();
    }

    app::Application app({ApplicationConstants::WIDTH,
                          ApplicationConstants::HEIGHT,
                          algo}, scheduler);

    app.Start();
  }
  catch (const std::exception &ex) {
    std::cerr << ex.what() << std::endl;
  }
}