#include "Scheduler.h"

namespace scheduler {

void Scheduler::ResetQueue(std::queue<unsigned int> &queue) {
  std::queue<unsigned int> empty;
  std::swap(queue, empty);
}

double Scheduler::GetAverageRuntime() const noexcept {
  return average_runtime_;
}

double Scheduler::GetAverageTimeout() const noexcept {
  return average_timeout_;
}

unsigned int Scheduler::GetProcessAmount() const noexcept {
  return processes_.size();
}

unsigned int Scheduler::GetProcessTime(unsigned int process_id) const noexcept {
  return processes_.at(process_id).time;
}

} // namespace scheduler
