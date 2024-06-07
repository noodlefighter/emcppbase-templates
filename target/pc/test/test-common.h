#pragma once

#include "etl/scheduler.h"
#include "embase_thread.h"

typedef etl::scheduler<etl::scheduler_policy_sequential_single, 2> SimpleScheduler;

class SchedulerWithThread : public SimpleScheduler, private embase::Thread
{
public:
  bool startScheduling() {
    return Thread::start();
  }
  void stopScheduling() {
    SimpleScheduler::exit_scheduler();
    Thread::join();
  }

private:
  int run() override {
    SimpleScheduler::start();
    return 0;
  }
};

