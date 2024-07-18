#ifndef MYKEYBOARD_H
#define MYKEYBOARD_H

#include "Display.h"
#include "Constants.h"

extern bool hasMinLenToValidate;

void drawKeyboard(String inputText, bool caps, int cursorX, int cursorY, int prevCursorX = -1, int prevCursorY = -1, bool refreshAll = false);
void handleKeyboardInput();

#endif // MYKEYBOARD_H
