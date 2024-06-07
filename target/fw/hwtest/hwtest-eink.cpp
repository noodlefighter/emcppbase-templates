/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "embase_platform.h"
#include "embase_log.h"

#include "epaper/epaper.h"
#include "epaper/bmp.h"

// define for White Black Red Epaper Module
//#define EPD_BWR

uint8_t image_bw[EPD_W_BUFF_SIZE * EPD_H];
#ifdef EPD_BWR
uint8_t image_red[EPD_W_BUFF_SIZE * EPD_H];
#endif

void app_entrance(int argc, char *argv[])
{
  uint8_t text[20];

  __emlog_info("nypx07 hwtest-eink");

  __emlog_info("\r\nWeAct Studio Core Board");
  __emlog_info("weactstudio.taobao.com");
  __emlog_info("weactstudio.aliexpress.com");
  __emlog_info("wwww.weact-tc.cn\r\n");
  __emlog_info("SystemClk:%d", SystemCoreClock);
  __emlog_info("Epaper Module Test");

  epd_io_init();

  epd_init();

#ifdef EPD_BWR
  epd_paint_newimage(image_bw, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

  epd_paint_newimage(image_red, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

  epd_paint_selectimage(image_bw);
  epd_paint_clear(EPD_COLOR_WHITE);

  epd_paint_selectimage(image_red);
  epd_paint_clear(EPD_COLOR_WHITE);
  epd_paint_showPicture((EPD_H - 250) / 2, (EPD_W - 122) / 2, 250, 122, gImage_4, EPD_COLOR_WHITE);

  epd_display(image_bw, image_red);
  epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);

  embase::__msleep(8000);

  epd_init();

  epd_paint_selectimage(image_bw);
  epd_paint_clear(EPD_COLOR_WHITE);
#ifdef EPD_213
  epd_paint_showString(10, 0, (uint8_t *)&"2.13 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
  epd_paint_showString(10, 50, (uint8_t *)&"with 250 x 122 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
#ifdef EPD_29
  epd_paint_showString(10, 0, (uint8_t *)&"2.9 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
  epd_paint_showString(10, 50, (uint8_t *)&"with 296 x 128 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
  epd_paint_showString(10, 29, (uint8_t *)&"Designed By WeAct Studio", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);

  epd_paint_selectimage(image_red);
  epd_paint_clear(EPD_COLOR_WHITE);

  sprintf((char *)&text, ">> Hello NYPX07.");
  epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_RED);

#if 0
  epd_paint_showString(10,100,(uint8_t *)&"CH32V103C8T6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_RED);
#else
  epd_paint_drawRectangle(10, 103, EPD_H - 10, 116, EPD_COLOR_RED, 1);
#endif

  epd_display(image_bw, image_red);
#else
  epd_paint_newimage(image_bw, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

  epd_paint_selectimage(image_bw);
  epd_paint_clear(EPD_COLOR_WHITE);
  epd_paint_showPicture((EPD_H - 250) / 2, (EPD_W - 122) / 2, 250, 122, gImage_4, EPD_COLOR_WHITE);

  epd_displayBW(image_bw);
  epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);

  embase::__msleep(5000);

  epd_init_partial();

  epd_paint_selectimage(image_bw);
  epd_paint_clear(EPD_COLOR_WHITE);
#ifdef EPD_213
  epd_paint_showString(10, 0, (uint8_t *)&"2.13 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
  epd_paint_showString(10, 50, (uint8_t *)&"with 250 x 122 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
#ifdef EPD_29
  epd_paint_showString(10, 0, (uint8_t *)&"2.9 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
  epd_paint_showString(10, 50, (uint8_t *)&"with 296 x 128 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
  epd_paint_showString(10, 29, (uint8_t *)&"Designed By WeAct Studio", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);

#if 0
  epd_paint_showString(10,100,(uint8_t *)&"CH32V103C8T6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_BLACK);
#else
  epd_paint_drawRectangle(10, 103, EPD_H - 10, 116, EPD_COLOR_BLACK, 1);
#endif

  sprintf((char *)&text, ">> Partial Mode");
  epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);

  epd_displayBW_partial(image_bw);

  embase::__msleep(1000);

  for (uint32_t i = 123; i < 8 * 123; i += 123)
  {
    sprintf((char *)&text, ">> Num=%d   ", (int)i);
    epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);

    epd_displayBW_partial(image_bw);

    embase::__msleep(100);
  }

  sprintf((char *)&text, ">> Hello World.");
  epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
  epd_displayBW_partial(image_bw);

  embase::__msleep(1000);

  epd_update();
#endif

  epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);

  // uint32_t tick, toggle_tick;
  // tick = 0;
  // toggle_tick = 250;
  while (1)
  {
    // tick++;
    // if (tick % toggle_tick == 0)
    // {
    //   board_led_toggle();
    // }
    // if (board_button_getstate())
    // {
    //   while (board_button_getstate())
    //   {
    //     Delay_Ms(50);
    //   }
    //   if (toggle_tick == 250)
    //   {
    //     toggle_tick = 100;
    //   }
    //   else
    //   {
    //     toggle_tick = 250;
    //   }
    // }
    embase::__msleep(1);
  }
}
