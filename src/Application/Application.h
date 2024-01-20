#pragma once

#include <memory>
#include <string>
#include <utility>

#include "../Window/Window.h"
#include "../Scheduler/Scheduler.h"

namespace app {

class Application {
 public:
  using Table = std::vector<std::vector<bool>>;

//  Application(std::shared_ptr<scheduler::Scheduler> scheduler) : window_(algo_to_title.at(scheduler.GetAlgorithm())),
//                                                                 scheduler_(std::move(scheduler)) {
//  }

  Application(std::shared_ptr<scheduler::Scheduler> scheduler) : window_("Title"),
                                                                 scheduler_(std::move(scheduler)) {
  }

  void Start();

 private:
  gui::Window window_;
  std::shared_ptr<scheduler::Scheduler> scheduler_;
  Table table_;
};

} // namespace app
