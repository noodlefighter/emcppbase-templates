#pragma once

#include <stdint.h>
#include <etl/intrusive_links.h>
#include <etl/intrusive_list.h>
#include "U8g2lib.h"

namespace U8Ui {

// 水平对齐风格
enum class AlignStyle {
  LEFT,
  CENTER,
  RIGHT,
};
// 垂直对齐风格
enum class ValignStyle {
  TOP,
  MIDDLE,
  BOTTOM,
};

typedef const uint8_t* Font_t;

struct Size {
  int16_t w;
  int16_t h;
};

struct Pos {
  int16_t x;
  int16_t y;
};

enum class Retval {
  OK = 0,
  FAIL = 1,
  EVENT_INTERCEPTED, // 事件被拦截，不要往下一层传递
};

enum class EventType {
  DRAW, // 重画
  KEY, // 按键输入
};

struct Event {
  Event(EventType type) : type(type) {}
  EventType type;
};
struct KeyEvent : Event {
  enum Keyact_t {
    KEY_CLICK,
    KEY_DOWN,
    KEY_UP,
  };

  KeyEvent(Keyact_t keyAction, int keyCode)
    : Event(EventType::KEY), KeyAction(keyAction), KeyCode(keyCode)
  {
  }

  Keyact_t KeyAction;
  int KeyCode;
};

class Object;
class StackableObject;

// 可被包含的UI对象接口，实现为入侵式链表
typedef etl::bidirectional_link<0> ObjectLink_t;
typedef etl::intrusive_list<Object, etl::bidirectional_link<0>> ObjectList_t;

// 可堆叠的UI对象接口，实现为入侵式链表
typedef etl::bidirectional_link<1> IStackable;
typedef etl::intrusive_list<StackableObject, IStackable> StackableObjectList;

// UI基础对象
class Object : public ObjectLink_t {
public:
  Object() : _size({0,0}), _pos({0,0}), _active(false), _parent(nullptr)
  {
  }

  void setSize(Size size) {
    _size = size;
  }
  Size getSize() {
    return _size;
  }
  void setPos(Pos pos) {
    _pos = pos;
  }
  Pos getPos() {
    return _pos;
  }
  void setActive(bool active) {
    _active = active;
  }
  bool isActive() {
    return _active;
  }

  void getRealXY(int &x, int &y) {
    x = _pos.x;
    y = _pos.y;
    Object *p = this;
    while (p->getParent() != nullptr) {
      p = p->getParent();
      x += p->getPos().x;
      y += p->getPos().y;
    }
  }

  void addChild(Object &obj) {
    _childList.push_back(obj);
    obj.setParent(this);
  }
  ObjectList_t& getChildList() {
    return _childList;
  }

  void setParent(Object *obj) {
    _parent = obj;
  }
  Object* getParent() {
    return _parent;
  }

  virtual void emitEvent(const Event &event);

  // 一些事件投递的wrapper
  void draw();
  void keyInput(const KeyEvent &keyEvent);

  static bool staticInit(U8G2 *u8g2);
  static U8G2* getU8G2();
  // 改进的updateDisplayArea2()，输入屏幕坐标，而不是tile坐标
  static void updateDisplayArea2(int x, int y, int w, int h);

protected:
  Size _size;
  Pos _pos;
  bool _active;
  Object *_parent;
  ObjectList_t _childList;

  virtual Retval _objectEventHandler(const Event &event) = 0; // UI对象内部的事件处理函数

private:
  static U8G2* _pU8g2;
};

class StackableObject : public Object, public IStackable {
};

// 可堆叠UI对象管理器，仅顶层响应事件，进入式逐层推入（push），返回时逐层弹出（pop）；类似浮动式窗口
class StackManager : public Object {
public:
  void stackPush(IStackable &obj) {
    _stackList.push_back(obj);
  }
  void stackPop() {
    _stackList.pop_back();
  }
  void stackPopAll() {
    _stackList.clear();
  }
protected:
  StackableObjectList _stackList;

  Retval _objectEventHandler(const Event &event) override;
};

}; // U8Ui
