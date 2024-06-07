#include "config.h"
#include "Application.h"
#include "ch32v20x.h"
#include "debug.h"
#include "embase_platform.h"
#include "embase_task.h"
#include "HAL.h"
#include "broadcaster.h"
#include <algorithm>

__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];
#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

// 为Application实现调度器
Scheduler g_SchedulerMainloop;
class BoardApplication : public Application {
public:
  Scheduler* getScheduler(SchedulerIndex sche) override {
    switch (sche) {
    case (SchedulerIndex::MAINLOOP):
      return &g_SchedulerMainloop;
    default:
      return nullptr;
    }
  }
};
BoardApplication g_Application;
Application* Application::getInstance()
{
  return &g_Application;
}

void hal_userloop_cb(void)
{
  g_SchedulerMainloop.start_noblock();
}

// 主循环
__attribute__((section(".highcode")))
__attribute__((noinline))
void Main_Circulation(void)
{
  while (1) {
    TMOS_SystemProcess();
  }
}

extern void embase_port_init();

int main(void)
{
  // 启动文件C++环境缺失，初始化静态全局对象
  typedef void (*function_t)();
  extern function_t __init_array_start;
  extern function_t __init_array_end;
  std::for_each(&__init_array_start, &__init_array_end, [](const function_t pfn) {
      pfn();
  });

  // 环境准备
  embase_port_init();
  USART_Printf_Init(115200);
  printf("SystemClk:%lu\r\n", (unsigned long)SystemCoreClock);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  // BLE环境
  printf("ble init: %s\r\n", VER_LIB);
  WCHBLE_Init();
  printf("hal init...\r\n");
  HAL_Init();

  extern tmosTaskID halTaskID;
  tmos_start_task(halTaskID, HAL_USER_LOOP, MS1_TO_SYSTEM_TIME(1));

  printf("Target Environment done!\r\n");

  extern void app_entrance(int argc, char *argv[]);
  app_entrance(0, nullptr);
  printf("Startup done!\r\n");


  Main_Circulation();
}
