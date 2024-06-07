#include "Application.h"
#include "MainGui.h"
#include "embase_log.h"

bool Application::init(void)
{
  // if (!MainGui::getInstance()->init()) {
  //   __emlog_info("GUI init fail...");
  //   return 1;
  // }
  // getScheduler()->add_task(*MainGui::getInstance());

  return true;
}
