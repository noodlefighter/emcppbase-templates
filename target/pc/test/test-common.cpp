#include "MainGui.h"
class DummyMainGui : public MainGui {
protected:
  bool initDisplayBuffer() override {
    return TRUE;
  }
  int getKey() override {
    return 0;
  }
};
DummyMainGui g_MainGui;
MainGui* MainGui::getInstance()
{
  return &g_MainGui;

}
