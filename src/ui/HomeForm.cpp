#include "HomeForm.h"
#include "embase_string.h"
#include "res/ui_res.h"

using namespace U8Ui;

HomeForm::HomeForm()
{
  setSize({UI_SCREEN_HEIGHT, UI_SCREEN_WIDTH});

  selfLabel.setPos({113, 92});
  selfLabel.setSize({50, 26});
  // selfLabel.setAlignStyle(AlignStyle::RIGHT);
  selfLabel.setValignStyle(ValignStyle::BOTTOM);
  selfLabel.setText("0000");
  addChild(selfLabel);

  leftLabel.setPos({2, 51});
  leftLabel.setSize({50, 26});
  // leftLabel.setAlignStyle(AlignStyle::RIGHT);
  leftLabel.setValignStyle(ValignStyle::BOTTOM);
  leftLabel.setText("0000");
  addChild(leftLabel);

  OpposLabel.setPos({81, 9});
  OpposLabel.setSize({50, 26});
  // OpposLabel.setAlignStyle(AlignStyle::RIGHT);
  OpposLabel.setValignStyle(ValignStyle::BOTTOM);
  OpposLabel.setText("0000");
  addChild(OpposLabel);

  rightLabel.setPos({146, 51});
  rightLabel.setSize({50, 26});
  // rightLabel.setAlignStyle(AlignStyle::RIGHT);
  rightLabel.setValignStyle(ValignStyle::BOTTOM);
  rightLabel.setText("0000");
  addChild(rightLabel);
}

Retval HomeForm::_objectEventHandler(const Event &event)
{
  if (event.type == EventType::DRAW) {
    onDraw();
  }
  return Retval::OK;
}

void HomeForm::onDraw()
{
  // auto sb = ScoreBoard::getInstance();

  getU8G2()->setFont(u8g2_font_unifont_t_symbols);
  // etl::string<32> str_self = embase::__string_format<32>(
  //   "%d", sb->getScore(ScoreBoard::Player::Self));
  // drawAreaUpdateUtf8(0, 32, str_self.c_str());

  auto u8g2 = getU8G2();
  // u8g2->drawXBMP(200, 32, battery_half.width, battery_half.height, battery_half.data);
  // updateDisplayArea2(200, 32, battery_half.width, battery_half.height);

  u8g2->drawXBMP(0, 0, uires_home_page.width, uires_home_page.height, uires_home_page.data);
  updateDisplayArea2(0, 0, uires_home_page.width, uires_home_page.height);
}
