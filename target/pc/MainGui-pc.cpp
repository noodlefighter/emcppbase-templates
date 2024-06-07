#include "MainGui.h"

extern "C" void u8g2_SetupBuffer_SDL_296x128(u8g2_t *u8g2, const u8g2_cb_t *u8g2_cb);

class PcMainGui : public MainGui {
protected:
  bool initDisplayBuffer() override {
    u8g2_SetupBuffer_SDL_296x128(_u8g2.getU8g2(), &u8g2_cb_r0);
    return TRUE;
  }
  int getKey() override {
    return u8g_sdl_get_key();
  }
};

PcMainGui g_PcMainGui;
MainGui* MainGui::getInstance()
{
  return &g_PcMainGui;
}
