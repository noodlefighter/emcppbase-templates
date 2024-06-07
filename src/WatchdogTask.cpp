#include "WatchdogTask.h"
#include "Application.h"

WatchdogTask g_WatchdogTask;
WatchdogTask* WatchdogTask::getInstance()
{
  return &g_WatchdogTask;
}

bool WatchdogTask::init()
{
  Application::getInstance()->getScheduler()->add_task(g_WatchdogTask);
  return true;
}

void WatchdogTask::intervalRun()
{
  printf("alive...\r\n");
  //todo: feed dog
}
