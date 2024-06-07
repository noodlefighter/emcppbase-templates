#pragma once

#include "embase_task.h"

class WatchdogTask : public embase::IntervalTask {
public:
  WatchdogTask() : IntervalTask(0)
  {
    setTaskInterval(10*1000);
  }
  bool init();
  void intervalRun() override final;

  static WatchdogTask* getInstance();
};
