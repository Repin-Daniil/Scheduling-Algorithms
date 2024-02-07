#include "Application.h"

namespace app {

void Application::Start() {
  while (window_.IsOpen()) {
    gui::UserChoice user_choice = window_.Tick();

    if (user_choice.type == gui::RESET) {
      Reset();
    } else if (user_choice.type == gui::ADD_PROCESS) {
      auto queue = scheduler_->AddProcess({scheduler_->GetProcessAmount(), user_choice.process_time});

      window_.SetTimeout(static_cast<double>(scheduler_->GetAverageTimeout()));
      window_.SetRuntime(static_cast<double>(scheduler_->GetAverageRuntime()));

      RenderTable(queue);
    }

    window_.Update(table_);
  }
}

void Application::Reset() {
  scheduler_->Reset();
  table_.clear();
  window_.SetRuntime(0.0);
  window_.SetTimeout(0.0);
}

void Application::RenderTable(std::queue<int> queue) {
  table_.clear();
  table_.resize(scheduler_->GetProcessAmount());

  std::vector<bool> is_finished(scheduler_->GetProcessAmount());
  std::vector<int> current_time(scheduler_->GetProcessAmount());

  while (!queue.empty()) {
    for (int i = 0; i < scheduler_->GetProcessAmount(); ++i) {
      if (is_finished[i]) {
        continue;
      }

      if (queue.front() == i) {
        table_[i].push_back(true);
        ++current_time[i];

        is_finished[i] = (current_time[i] == scheduler_->GetProcessTime(i));
      } else {
        table_[i].push_back(false);
      }
    }

    queue.pop();
  }
}

}  // namespace app
