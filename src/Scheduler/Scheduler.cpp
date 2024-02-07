#include "Scheduler.h"

namespace scheduler {

void Scheduler::Reset() {
  ResetQueues();
  processes_.clear();
}

void Scheduler::ResetQueues() {
  std::queue<int> empty;
  std::swap(job_queue_, empty);
  average_timeout_ = average_runtime_ = 0;

  ResetSpecific();
}

void Scheduler::ResetSpecific() {
}

double Scheduler::GetAverageRuntime() const noexcept {
  return average_runtime_;
}

double Scheduler::GetAverageTimeout() const noexcept {
  return average_timeout_;
}

int Scheduler::GetProcessAmount() const noexcept {
  return processes_.size();
}

int Scheduler::GetProcessTime(int process_id) const {
  if (process_id >= processes_.size()) {
    throw std::invalid_argument("No process");
  }

  return processes_.at(process_id).time;
}

std::vector<Process> Scheduler::GetProcesses() const noexcept {
  return processes_;
}

Scheduler::Queue Scheduler::GetJobQueue() const noexcept {
  return job_queue_;
}

Algorithm Scheduler::GetAlgorithm() const noexcept {
  return algorithm_;
}

bool Process::operator<(const Process &other) const {
  if (time == other.time) {
    return (entry_time < other.entry_time);
  }

  return time < other.time;
}

bool Process::operator>(const Process &other) const {
  if (time == other.time) {
    return (entry_time > other.entry_time);
  }

  return time > other.time;
}

}  // namespace scheduler
