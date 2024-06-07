#include "ch32v20x.h"
#include "HAL.h"
#include "broadcaster.h"

void app_entrance(int argc, char *argv[])
{
  printf("Broadcaster init...\r\n");
  GAPRole_BroadcasterInit();
  Broadcaster_Init();
}
