#include "drv_trf796x.h"

#include "trf/trf796x.h"
#include "trf/iso15693.h"

// 一些全局变量.... TI怎么写出这种烂风格代码，适配起来真恼火
extern "C" {
uint8_t buf[300];
uint8_t i_reg = 0;
uint8_t irq_flag = 0;
int8_t rxtx_state = 0;
uint8_t rx_error_flag = 0;
uint8_t stand_alone_flag = 0;
uint8_t host_control_flag = 0;
};

bool DrvTrf796x::init(SPIClass *spi, etl::ischeduler *scheduler)
{
  // 上电
	// TRF_ENABLE;							// P1.0 = 1, EN pin on the TRF 796x
	embase::__msleep(1);				// wait until system clock started


  Trf796xCommunicationSetup();		// settings for communication with TRF
  Trf796xInitialSettings();			// Set MCU Clock Frequency to 6.78 MHz and OOK Modulation

	embase::__msleep(10);
  Trf796xReConfig();

  _spi = spi;

  scheduler->add_task(*this);
  etl::task::set_task_running(true);
  return true;
}


void DrvTrf796x::deinit()
{
  etl::task::set_task_running(false);
}


void DrvTrf796x::findTags()
{
  Iso15693FindTag();			// detects ISO15693 in stand-alone mode
}

async_evt DrvTrf796x::_taskEntry(struct async *pt)
{

}
