#pragma once

#include "embase_task.h"

class Scheduler : public embase::TaskScheduler<etl::scheduler_policy_sequential_single, 10>
{
};

class Application {
public:
  bool init();

  enum class SchedulerIndex {
    MAINLOOP, // 主循环调度器
  };
  virtual Scheduler* getScheduler(SchedulerIndex sche = SchedulerIndex::MAINLOOP) = 0;

  static Application* getInstance();
};
