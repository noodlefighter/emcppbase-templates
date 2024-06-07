#include "Application.h"
#include "MainGui.h"
#include "WatchdogTask.h"
#include <stdio.h>

void app_entrance(int argc, char *argv[])
{
  // Application
  if (!Application::getInstance()->init()) {
    printf("Application init fail...");
  }

  // MainGui
  if (!MainGui::getInstance()->init()) {
    printf("MainGui init fail...");
  }

  WatchdogTask::getInstance()->init();

}
