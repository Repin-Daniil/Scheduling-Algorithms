#include "Scheduler.h"

namespace scheduler {

Scheduler::Queue Scheduler::AddProcess(Process new_process) {
  if (algorithm_ == FCFS) {
    processes_.push_back(new_process);

    if (!job_queue_.empty()) {
      duration_of_waiting_ += duration_of_waiting_ + processes_[job_queue_.back()].time;
      duration_of_execution_ += last_execution_time_;
    }

    last_execution_time_ += new_process.time;
    duration_of_execution_ += new_process.time;

    average_timeout_ = duration_of_waiting_ / (processes_.size());
    average_runtime_ = duration_of_execution_ / (processes_.size());

    for (unsigned int i = 0; i < new_process.time; ++i) {
      job_queue_.push(new_process.id);
    }
  }

  if (algorithm_ == RR) {
    processes_.push_back(new_process);

    average_timeout_ = average_runtime_ = 0;

    ResetQueue(ready_queue_);
    ResetQueue(job_queue_);

    // Готовим очередь, добавляя все процессы
    for (auto &process : processes_) {
      ready_queue_.push(process.id);
    }

    unsigned int time = 0;
    std::vector<unsigned int> current_process_time(processes_.size(), 0);

    while (!ready_queue_.empty()) {
      ++time;
      auto process_id = ready_queue_.front();
      job_queue_.push(process_id);

      if (++current_process_time[process_id] < processes_[process_id].time) {
        ready_queue_.push(process_id);
      }
      else if(current_process_time[process_id] ==  processes_[process_id].time) {
        average_timeout_ += time - current_process_time[process_id];
        average_runtime_ += time;
      }

      ready_queue_.pop();
    }

    average_timeout_ /= processes_.size();
    average_runtime_ /= processes_.size();
  }

  return job_queue_;
}

void Scheduler::ResetQueue(std::queue<unsigned int> &queue) {
  std::queue<unsigned int> empty;
  std::swap(queue, empty);
}

void Scheduler::Reset() {
  ResetQueue(job_queue_);
  ResetQueue(ready_queue_);
  processes_.clear();

  average_timeout_ = average_runtime_ = 0;
  duration_of_execution_ = duration_of_waiting_ = last_execution_time_ = 0;
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
