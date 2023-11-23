#include <iostream>
#include "Application/Application.h"
#include "Scheduler/Lab_1/SchedulerFCFS.h"
#include "Scheduler/Lab_2/SchedulerRR.h"
#include "Scheduler/Lab_2/SchedulerSJF.h"
#include "Scheduler/Lab_3/SchedulerRR_SJF.h"
#include "Scheduler/Lab_3/SchedulerPSJF.h"

int main() {
  try {
    std::string input;
    std::cout << "Algorithm: ";
    std::cin >> input;

    Algorithm algo = string_to_algo.at(input);
    std::shared_ptr<scheduler::Scheduler> scheduler;

    if (algo == Algorithm::FCFS) {
      scheduler = std::make_shared<scheduler::SchedulerFCFS>();
    } else if (algo == Algorithm::RR) {
      scheduler = std::make_shared<scheduler::SchedulerRR>();
    } else if (algo == Algorithm::SJF) {
      scheduler = std::make_shared<scheduler::SchedulerSJF>();
    } else if (algo == Algorithm::PSJF) {
      scheduler = std::make_shared<scheduler::SchedulerPSJF>();
    } else if (algo == Algorithm::RR_SJF) {
      scheduler = std::make_shared<scheduler::SchedulerRR_SJF>();
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
