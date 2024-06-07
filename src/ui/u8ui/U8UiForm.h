#pragma once

#include "u8ui/U8Ui.h"

namespace U8Ui {

class UiForm : public StackableObject {
public:

protected:
  Retval _objectEventHandler(const Event &event) override;
};

}; // namespace U8Ui

