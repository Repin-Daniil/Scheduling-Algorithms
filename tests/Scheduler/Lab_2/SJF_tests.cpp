#define CATCH_CONFIG_MAIN
#include "../../../catch.hpp"

#include "../../../src/Scheduler/Lab_2/SchedulerSJF.h"

using namespace scheduler;

namespace Catch {

template<>
struct StringMaker<Scheduler::Queue> {
  static std::string convert(Scheduler::Queue const &queue) {
    std::stringstream ss;
    Scheduler::Queue copy(queue);

    while (!copy.empty()) {
      ss << copy.front() << " ";
      copy.pop();
    }

    return ss.str();
  }
};

} // namespace Catch

SCENARIO("Scheduler SJF") {
  GIVEN("A SJF scheduler") {
    SchedulerSJF scheduler;

    SECTION("Initially job queue is empty and everything == 0") {
      CHECK(scheduler.GetProcesses().empty());
      CHECK(scheduler.GetJobQueue().empty());
      CHECK(scheduler.GetProcessAmount() == 0);
      CHECK(scheduler.GetAverageRuntime() == 0.0);
      CHECK(scheduler.GetAverageTimeout() == 0.0);
      CHECK_THROWS_AS(scheduler.GetProcessTime(1), std::invalid_argument);
    }

    WHEN("we add first process with time = 13") {
      scheduler.AddProcess({scheduler.GetProcessAmount(), 13});

      THEN("it add new process and calculate average runtime and timeout") {
        CHECK(scheduler.GetProcessAmount() == 1);
        CHECK(scheduler.GetJobQueue().size() == 13);
        {
          Scheduler::Queue correct_queue({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
          CHECK(correct_queue == scheduler.GetJobQueue());
        }
        CHECK(scheduler.GetAverageTimeout() == 0.0);
        CHECK(scheduler.GetAverageRuntime() == 13.0);

        AND_WHEN("we add second process with time = 4") {
          scheduler.AddProcess({scheduler.GetProcessAmount(), 4});

          THEN("it add new process and calculate average runtime and timeout") {
            CHECK(scheduler.GetProcessAmount() == 2);
            CHECK(scheduler.GetJobQueue().size() == 17);
            {
              Scheduler::Queue correct_queue({1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
              CHECK(correct_queue == scheduler.GetJobQueue());
            }
            CHECK(scheduler.GetAverageTimeout() == 2.0);
            CHECK(scheduler.GetAverageRuntime() == 10.5);

            AND_WHEN("we add third process with time = 1") {
              scheduler.AddProcess({scheduler.GetProcessAmount(), 1});

              THEN("it add new process and calculate average runtime and timeout") {
                CHECK(scheduler.GetProcessAmount() == 3);
                CHECK(scheduler.GetJobQueue().size() == 18);
                {
                  Scheduler::Queue correct_queue({2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
                  CHECK(correct_queue == scheduler.GetJobQueue());
                }
                CHECK(scheduler.GetAverageTimeout() == 2.0);
                CHECK(scheduler.GetAverageRuntime() == 8.0);
              }
            }
          }
        }
      }
    }

    WHEN("we add processes with the same time and want to reset") {
      scheduler.AddProcess({scheduler.GetProcessAmount(), 10});
      scheduler.AddProcess({scheduler.GetProcessAmount(), 10});
      scheduler.AddProcess({scheduler.GetProcessAmount(), 10});

      THEN("processes are executed sequentially") {
        CHECK(scheduler.GetProcessAmount() == 3);
        CHECK(scheduler.GetJobQueue().size() == 30);
        {
          Scheduler::Queue correct_queue({0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                          1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                          2, 2, 2, 2, 2, 2, 2, 2, 2, 2});
          CHECK(correct_queue == scheduler.GetJobQueue());
        }
        CHECK(scheduler.GetAverageTimeout() == 10.0);
        CHECK(scheduler.GetAverageRuntime() == 20.0);

        AND_WHEN("we want to reset") {
          scheduler.Reset();

          THEN("everything = 0 and job queue is empty") {
            CHECK(scheduler.GetJobQueue().empty());
            CHECK(scheduler.GetProcessAmount() == 0);
            CHECK(scheduler.GetAverageTimeout() == 0.0);
            CHECK(scheduler.GetAverageRuntime() == 0.0);

            AND_WHEN("we want to add normal process with time = 4") {
              scheduler.AddProcess({scheduler.GetProcessAmount(), 4});

              THEN("it add new process and calculate average runtime and timeout") {
                CHECK(scheduler.GetProcessAmount() == 1);
                CHECK(scheduler.GetJobQueue().size() == 4);
                {
                  Scheduler::Queue correct_queue({0, 0, 0, 0});
                  CHECK(correct_queue == scheduler.GetJobQueue());
                }
                CHECK(scheduler.GetAverageTimeout() == 0.0);
                CHECK(scheduler.GetAverageRuntime() == 4.0);
              }
            }
          }
        }
      }
    }

    WHEN("we add processes with zero time") {
      scheduler.AddProcess({0, 0});

      THEN("nothing changes") {
        CHECK(scheduler.GetJobQueue().empty());
        CHECK(scheduler.GetProcessAmount() == 0);
        CHECK(scheduler.GetAverageTimeout() == 0.0);
        CHECK(scheduler.GetAverageRuntime() == 0.0);

        AND_WHEN("we add normal process with time = 1") {
          scheduler.AddProcess({0, 1});

          THEN("it add new process and calculate average runtime and timeout") {
            CHECK(scheduler.GetProcessAmount() == 1);
            CHECK(scheduler.GetJobQueue().size() == 1);
            {
              Scheduler::Queue correct_queue({0});
              CHECK(correct_queue == scheduler.GetJobQueue());
            }
            CHECK(scheduler.GetAverageTimeout() == 0.0);
            CHECK(scheduler.GetAverageRuntime() == 1.0);
          }
        }
      }
    }
  }
}