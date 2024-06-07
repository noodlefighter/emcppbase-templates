#include "Application.h"
#include "embase_macros.h"
#include "embase_log.h"

// 为Application实现调度器
Scheduler g_Scheduler;
class PcApplication : public Application {
public:
  Scheduler* getScheduler(SchedulerIndex sche) override {
    return &g_Scheduler;
  }
};
PcApplication g_Application;
Application* Application::getInstance()
{
  return &g_Application;
}

int main(void)
{

  extern void app_entrance(int argc, char *argv[]);
  app_entrance(0, nullptr);

  while (1) {
    g_Scheduler.start();
  }

  return 0;
}
