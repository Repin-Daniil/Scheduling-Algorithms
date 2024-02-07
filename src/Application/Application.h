#pragma once

#include <memory>
#include <string>
#include <utility>
#include <queue>
#include <vector>

#include "../Window/Window.h"
#include "../Scheduler/Scheduler.h"

namespace app {

class Application {
 public:
  using Table = std::vector<std::vector<bool>>;

  explicit Application(std::unique_ptr<scheduler::Scheduler> scheduler)
      : window_(algo_to_title.at(scheduler->GetAlgorithm()).data()),
        scheduler_(std::move(scheduler)) {
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
