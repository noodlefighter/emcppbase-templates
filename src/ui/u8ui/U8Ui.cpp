#include "u8ui/U8Ui.h"

#include "U8UiForm.h"

namespace U8Ui {

void Object::draw()
{
  emitEvent(Event(EventType::DRAW));
}

void Object::keyInput(const KeyEvent &keyEvent)
{
  emitEvent(keyEvent);
}

void Object::emitEvent(const Event &event)
{
  if (event.type == EventType::DRAW) {
    // 向下传播
    _objectEventHandler(event);
    if (!_childList.empty()) {
      for (auto &i : _childList) {
        i.emitEvent(event);
      }
    }
  }
  else if (event.type == EventType::KEY) {
    // 向上传播
    _objectEventHandler(event);
    if (_parent) {
      _parent->emitEvent(event);
    }
  }
  else {
    // 不传播
    _objectEventHandler(event);
  }
}

Retval StackManager::_objectEventHandler(const Event &event)
{
  if (_stackList.empty()) {
    return Retval::OK;
  }
  StackableObject &topObject = _stackList.back();

  UiForm *uiFrom = dynamic_cast<UiForm*>(&topObject);
  uiFrom->emitEvent(event);
  // topObject.emitEvent(event);
  return Retval::OK;
}

U8G2* Object::_pU8g2 = nullptr;

bool Object::staticInit(U8G2 *u8g2)
{
  _pU8g2 = u8g2;
  return true;
}
U8G2* Object::getU8G2()
{
  assert(_pU8g2 != nullptr);
  return _pU8g2;
}
void Object::updateDisplayArea2(int x, int y, int w, int h)
{
  assert(_pU8g2 != nullptr);
  uint8_t tx = x / 8;
  uint8_t ty = y / 8;
  uint8_t tw = (x + w + 7) / 8 - tx;
  uint8_t th = (y + h + 7) / 8 - ty;

  if (tx+tw > _pU8g2->getBufferTileWidth()) {
    tw = _pU8g2->getBufferTileWidth() - tx;
  }
  if (ty+th > _pU8g2->getBufferTileHeight()) {
    th = _pU8g2->getBufferTileHeight() - ty;
  }
  _pU8g2->updateDisplayArea(tx, ty, tw, th);
}

}; // namespace U8Ui
