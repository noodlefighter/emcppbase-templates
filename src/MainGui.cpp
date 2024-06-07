#include "MainGui.h"
#include "Application.h"
#include "embase_macros.h"
#include <unistd.h>
#include <string.h>

using namespace U8Ui;

bool MainGui::init(void)
{
  do {
    EM_BREAK_IF(!initDisplayBuffer());
    _u8g2.initDisplay();
    _u8g2.setPowerSave(0);

    // 将HomePage窗体压入对象堆栈
    _stackMannager.stackPush(_homeForm);
    Object::staticInit(&_u8g2);

    Application::getInstance()->getScheduler()->add_task(*this);
    _logger.info("MainGui init ok");
    return true;
  } while (1);
  _logger.error("MainGui init failed!");
  return false;
}

#if 1
async_evt MainGui::_taskEntry(struct async *pt)
{
  async_begin(pt);

  _stackMannager.draw();
  while(1) {
    async_yield;
    // if (hasInput()) {
    //   // ...
    // }
    // if (scroceChanged()) {
    //   // ...
    // }
  }
  async_end;
}
#else // u8g2测试
async_evt MainGui::_taskEntry(struct async *pt)
{
  async_begin(pt);

  // _u8g2.setFont(u8g2_font_wqy15_t_gb2312);
  _u8g2.setFont(u8g2_font_unifont_t_symbols);
  // _u8g2.drawUTF8(2, 20, "试着按任意键");
  _u8g2.drawUTF8(2, 20, "try any key");
  _u8g2.sendBuffer();
  while(1) {
    async_yield;

    int c = getKey();
    if (c > 0) {
      _logger.info("key: %c", c);

      if (cnt == 0) {
        _u8g2.clearDisplay();
      }

      char buf[20];
      _u8g2.clearBuffer();
      // _u8g2.setFont(u8g2_font_wqy15_t_gb2312);
      // o = _u8g2.drawUTF8(2, 20, "你好世界abc");
      o = _u8g2.drawUTF8(2, 20, "hello world abc");
      snprintf(buf, sizeof(buf), "%d", cnt++);
      _u8g2.drawUTF8(5 + o, 20, buf);
      // _u8g2.setFont(u8g2_font_unifont_t_symbols);
      _u8g2.drawUTF8(5, 40, "Snowman: ☃");
      _u8g2.sendBuffer();
    }

    // 移动的方块，局部刷新测试
    else {
      // _u8g2.clearBuffer();
      _u8g2.setDrawColor(0);
      _u8g2.drawBox(block_x, block_y, block_w, block_w);
      if (++block_x >= _u8g2.getWidth()) {
        block_x = 0;
      }
      _u8g2.setDrawColor(1);
      _u8g2.drawBox(block_x, block_y, block_w, block_w);
      // 使用改进过的updateDisplayArea()进行局部刷新
      Object::updateDisplayArea2(0, block_y, _u8g2.getDisplayWidth(), block_w);
    }

  }

  async_end;
}
#endif
