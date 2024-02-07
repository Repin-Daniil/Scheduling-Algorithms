#pragma once

#include <memory>
#include <string>
#include <utility>
#include <queue>
#include <vector>

#include "../Window/Window.h"
#include "../Scheduler/Scheduler.h"
#include "../Scheduler/SchedulerFactory.h"

namespace app {

class Application {
 public:
  using Table = std::vector<std::vector<bool>>;

  explicit Application(Algorithm algo) : window_(algo_to_title.at(algo).data()) {
    scheduler_ = scheduler::SchedulerFactory::CreateScheduler(algo);
  }

  void Start();

 private:
  void Reset();
  void RenderTable(std::queue<int> queue);

 private:
  gui::Window window_;
  std::unique_ptr<scheduler::Scheduler> scheduler_;
  Table table_;
};

}  // namespace app
