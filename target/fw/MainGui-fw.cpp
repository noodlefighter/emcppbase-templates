#include "MainGui.h"

class BoardMainGui : public MainGui {
protected:
  bool initDisplayBuffer() override {
    // todo:
    return TRUE;
  }
  int getKey() override {
    // todo:
    return 0;
  }
};

BoardMainGui g_MainGui;
MainGui* MainGui::getInstance()
{
  return &g_MainGui;
}
