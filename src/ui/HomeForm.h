#pragma once

#include "u8ui/U8UiForm.h"
#include "u8ui/U8UiLabel.h"
#include "ui_define.h"

class HomeForm : public U8Ui::UiForm {
public:
  HomeForm();

  U8Ui::UiLabel selfLabel;
  U8Ui::UiLabel leftLabel;
  U8Ui::UiLabel OpposLabel;
  U8Ui::UiLabel rightLabel;

  U8Ui::UiLabel selfDiffLabel;
  U8Ui::UiLabel leftDiffLabel;
  U8Ui::UiLabel OpposDiffLabel;
  U8Ui::UiLabel rightDiffLabel;

protected:
  U8Ui::Retval _objectEventHandler(const U8Ui::Event &event) override;

private:
  void onDraw();
};
