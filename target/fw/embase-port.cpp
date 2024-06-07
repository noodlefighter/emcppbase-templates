#include "embase-port.h"
#include "embase_platform.h"
#include "ch32v20x.h"
#include "core_riscv.h"
#include "system_ch32v20x.h"

void embase_port_init()
{
  assert(SystemCoreClock == 72000000);
  SysTick->SR=0;
  SysTick->CNT=0;
  SysTick->CTLR=0x1;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
}

namespace embase {

/*
  note: __get_sys_timestamp()根据72MHz优化，systick时钟源为HCLK/8，72/8=9MHz
    9000000Hz -> 1s
    9000tims -> 1ms
    9times -> 1us
    故以2^13(8192) 近似 9000，比实际的时间稍快
*/
TimeMs_t __get_systick_ms()
{
  return (TimeMs_t)(SysTick->CNT >> 13);
}
TimeUs_t __get_systick_us()
{
  return (TimeUs_t)(SysTick->CNT >> 3);
}

void __msleep(UINT32 v)
{
  TimeMs_t start = __get_systick_ms();
  while (__get_systick_ms() - start < v);
}

void __usleep(UINT32 v)
{
  UINT64 start = SysTick->CNT;
  UINT64 diff = v*9;
  while (SysTick->CNT - start < diff);
}

} // embase


// Arduino适配
#include "Arduino.h"

static GPIO_TypeDef* const _portTb[] = {
  GPIOA, GPIOB, GPIOC, GPIOD, GPIOE
};
extern "C" {
void pinMode(uint8_t pin, uint8_t mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_TypeDef *gpioPort = _portTb[__PIN_TO_PORT(pin)];
  uint8_t gpioPin = BIT(__PIN_TO_NUM(pin));

  GPIOMode_TypeDef gpioMode;
  switch (mode) {
  case OUTPUT:
    gpioMode = GPIO_Mode_Out_PP;
    break;
  case OUTPUT_OPEN_DRAIN:
    gpioMode = GPIO_Mode_Out_OD;
    break;

  case INPUT:
  case INPUT_FLOATING:
    gpioMode = GPIO_Mode_IN_FLOATING;
    break;
  case INPUT_PULLUP:
    gpioMode = GPIO_Mode_IPU;
    break;
  case INPUT_PULLDOWN:
    gpioMode = GPIO_Mode_IPD;
    break;
  case INPUT_ANALOG:
    gpioMode = GPIO_Mode_AIN;
    break;
  default:
    assert(0);
  }
  GPIO_InitStructure.GPIO_Mode = gpioMode;
  GPIO_InitStructure.GPIO_Pin = gpioPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(gpioPort, &GPIO_InitStructure);
}

void digitalWrite(uint8_t pin, uint8_t val)
{
  GPIO_TypeDef *gpioPort = _portTb[__PIN_TO_PORT(pin)];
  uint8_t gpioPin =  BIT(__PIN_TO_NUM(pin));
  GPIO_WriteBit(gpioPort, gpioPin, val ? Bit_SET : Bit_RESET);
}

int digitalRead(uint8_t pin)
{
  GPIO_TypeDef *gpioPort = _portTb[__PIN_TO_PORT(pin)];
  uint8_t gpioPin =  BIT(__PIN_TO_NUM(pin));
  return GPIO_ReadInputDataBit(gpioPort, gpioPin);
}

} // extern "C"

SoftwareSPI SPI;
