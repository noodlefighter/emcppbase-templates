#pragma once

#include "embase_task.h"
#include "SPI.h" // Arduino SPI

class DrvTrf796x : public embase::AsyncTask {
public:
  DrvTrf796x() : AsyncTask(1, 1)
  {
  }

  bool init(SPIClass *spi, etl::ischeduler *scheduler);
  void deinit();

  void findTags();

private:
  SPIClass *_spi;

  async_evt _taskEntry(struct async *pt);
};
