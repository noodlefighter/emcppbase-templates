#include "Application.h"
#include <stdio.h>

void app_entrance(int argc, char *argv[])
{
  printf("App2");
  // Application
  if (!Application::getInstance()->init()) {
    printf("Application init fail...");
  }
}
