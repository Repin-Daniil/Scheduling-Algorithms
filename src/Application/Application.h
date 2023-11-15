#pragma once

#include <memory>
#include <string>
#include <utility>
#include "../Window/Window.h"
#include "../Scheduler/Scheduler.h"

namespace app {

struct Settings {
  unsigned int width;
  unsigned int height;

  Algorithm algorithm;
};

class Application {
 public:
  using Table = std::vector<std::vector<bool>>;

  Application(Settings settings, std::shared_ptr<scheduler::Scheduler> scheduler) : window_(settings.width,
                                                                                            settings.height,
                                                                                            algo_to_title.at(settings.algorithm).data()),
                                                                                    scheduler_(std::move(scheduler)) {
  }

  void Start();

 private:
  gui::Window window_;
  std::shared_ptr<scheduler::Scheduler> scheduler_;
  Table table_;
};

} // namespace app
