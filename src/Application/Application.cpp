#include "Application.h"

namespace app {

void Application::Start() {
  while (window_.IsOpen()) {
    auto input = window_.Tick();

    if (input) {
      unsigned int time = *input;

      if (time == 0) { // Reset
        scheduler_.Reset();
        table_.clear();
        window_.SetRuntime(0.0);
        window_.SetTimeout(0.0);
      } else {
        auto queue = scheduler_.AddProcess({scheduler_.GetProcessAmount(), time});

        window_.SetTimeout(static_cast<double>(scheduler_.GetMiddleTimeout()));
        window_.SetRuntime(static_cast<double>(scheduler_.GetMiddleRuntime()));

        table_.clear();
        table_.resize(scheduler_.GetProcessAmount());

        std::vector<bool> is_finished(scheduler_.GetProcessAmount());

        while (!queue.empty()) {
          for (size_t i = 0; i < scheduler_.GetProcessAmount(); ++i) {
            if (is_finished[i]) {
              continue;
            }

            is_finished[i] = is_finished[i] + (queue.front().id == i);

            for (size_t j = 0; j < queue.front().time; ++j) {
              table_[i].push_back(is_finished[i]);
            }
          }

          queue.pop();
        }
      }
    }

    window_.Clear();

    if (!table_.empty()) {
      window_.DrawTable(table_);
    }

    window_.Update();
  }
}

} // namespace app
