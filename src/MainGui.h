#pragma once

#include "embase_task.h"
#include "embase_log.h"

#include "HomeForm.h"
#include "MenuForm.h"

class MainGui : public embase::AsyncTask {
public:
  const char *MODULE_NAME = "MainGui";
  MainGui() : AsyncTask(1,1), _logger(MODULE_NAME) {}

  virtual bool init();

  static MainGui* getInstance();

protected:
  embase::Logger _logger;
  U8G2 _u8g2;

  U8Ui::StackManager _stackMannager;
  HomeForm _homeForm;
  // MenuForm _menuForm;

  // 需在子类中适配
  virtual bool initDisplayBuffer() = 0;
  virtual int getKey() = 0;

private:
  int cnt = 0, o;
  int block_x = 0;
  int block_y = 42;
  const int block_w = 20;

  async_evt _taskEntry(struct async *pt) override final;
};
