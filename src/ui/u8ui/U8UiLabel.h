#pragma once

#include "u8ui/U8Ui.h"
#include <etl/string.h>

namespace U8Ui {

class UiLabel : public Object {
public:
  static const size_t MAX_STR_LEN = 32;
  typedef etl::string<MAX_STR_LEN> String_t;

  UiLabel()
    : _alignStyle(AlignStyle::LEFT),
      _valignStyle(ValignStyle::MIDDLE),
      _font(nullptr),
      _color(1),
      _text("")
  {
  }

  void setAlignStyle(AlignStyle alignStyle) {
    _alignStyle = alignStyle;
  }
  void setValignStyle(ValignStyle valignStyle) {
    _valignStyle = valignStyle;
  }
  void setFont(Font_t font) {
    _font = font;
  }
  void setColor(uint8_t colorIndex) {
    _color = colorIndex;
  }

  void setText(const String_t &text) {
    _text = text;
  }

protected:
  Retval _objectEventHandler(const Event &event) override;

private:
  AlignStyle _alignStyle;
  ValignStyle _valignStyle;
  Font_t _font;
  uint8_t _color;
  String_t _text;
};

}; // namespace U8Ui

