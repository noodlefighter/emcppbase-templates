#include "Arduino.h"
#include "embase-port.h"
#include "embase_log.h"
#include "embase_platform.h"

// LED闪烁测试
#if 1
#define PIN_LED         PIN_PB5
#define STR(n)          #n
void app_entrance(int argc, char *argv[])
{
  __emlog_info("hwtest-led arduino digitalWrite, " STR(PIN_LED));
  pinMode(PIN_LED, OUTPUT);
  while(1) {
    __emlog_info("high");
    digitalWrite(PIN_LED, HIGH);
    embase::__msleep(1000);

    __emlog_info("low");
    digitalWrite(PIN_LED, LOW);
    embase::__msleep(1000);
  }
}

#else

#include "ch32v20x.h"

void app_entrance(int argc, char *argv[])
{
  GPIO_InitTypeDef GPIO_InitStructure = {0};

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  __emlog_info("hwtest-led gpio test");
  while (1) {
    __emlog_info("high");
    GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);
    embase::__msleep(1000);

    __emlog_info("low");
    GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_RESET);
    embase::__msleep(1000);
  }

}
#endif
