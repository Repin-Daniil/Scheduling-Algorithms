#pragma once

#include <string>
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

  Application(Settings settings) : window_(settings.width, settings.height, algo_to_title.at(settings.algorithm).data()),
                                   scheduler_(settings.algorithm) {
  }

  void Start();

 private:
  gui::Window window_;
  scheduler::Scheduler scheduler_;
  Table table_;
};

} // namespace app
