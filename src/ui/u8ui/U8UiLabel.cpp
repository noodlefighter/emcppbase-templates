#include "U8UiLabel.h"

namespace U8Ui {

Retval UiLabel::_objectEventHandler(const Event &event)
{
  if (event.type == EventType::DRAW) {
    int realX, realY; // 相对坐标(0,0)的绝对坐标
    getRealXY(realX, realY);

    // Font Style
    if (_font != nullptr) {
      getU8G2()->setFont(_font);
    }
    getU8G2()->setFontMode(0);

    // Draw Background
    getU8G2()->setDrawColor((0 == _color) ? 1 : 0);
    getU8G2()->drawBox(realX, realY, _size.w, _size.h);

    // Draw Text
    int strX, strY;
    getU8G2()->setDrawColor(_color);
    switch (_valignStyle) {
    case ValignStyle::TOP:
      strY = realY;
      getU8G2()->setFontPosTop();
      break;
    case ValignStyle::MIDDLE:
      strY = realY + _size.h/2;
      getU8G2()->setFontPosCenter();
      break;
    case ValignStyle::BOTTOM:
      strY = realY + _size.h;
      getU8G2()->setFontPosBottom();
      break;
    default:
      assert(false);
    }
    switch (_alignStyle) {
    case AlignStyle::LEFT:
      strX = realX;
      break;
    case AlignStyle::CENTER:
      strX = realX + _size.w/2;
      break;
    case AlignStyle::RIGHT:
      strX = realX + _size.w;
      break;
    default:
      assert(false);
    }
    getU8G2()->drawStr(strX, strY, _text.c_str());
    updateDisplayArea2(realX, realY, _size.w, _size.h);
  }
  return Retval::OK;
}

}; // namespace U8Ui
