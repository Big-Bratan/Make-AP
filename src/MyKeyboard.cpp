#include "MyKeyboard.h"

bool hasMinLenToValidate = false;

// Define the keyboard keys
char keys[4][12][2] = {
    {{'1', '!'}, {'2', '@'}, {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'}, {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'}, {'-', '_'}, {'=', '+'}},
    {{'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'}, {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'}, {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'}},
    {{'a', 'A'}, {'s', 'S'}, {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'}, {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'}, {'"', '\''}, {'|', '\\'}},
    {{'\\', '|'}, {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'}, {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'}, {'.', '>'}, {'?', '/'}, {'/', '/'}}};

// Define the top keys
const char *specialKeys[] = {"OK", "CAP", "DEL", "SPACE"};

/***************************************************************************************
** Function name: drawInputField
** Description:   Draw the input field.
***************************************************************************************/
void drawInputField(String inputText, String error = "") {
  Serial.print("DRAWING INPUT FIELD \n");
  // Calculate responsive dimensions
  int margin = 3 * SCALE_FACTOR;
  int fieldHeight = 23;
  
  // Erase & redraw input field
  M5.Display.fillRect(margin, 27, WIDTH - (margin * 2), fieldHeight, BGCOLOR);
  M5.Display.drawRect(margin, 27, WIDTH - (margin * 2), fieldHeight, COLOR_PRIMARY);
  M5.Display.setTextColor(TFT_WHITE, BGCOLOR);

  // Adjust text size depending on its length and screen size
  int maxChars = (deviceConfig.type == DEVICE_M5CORE2) ? 20 : 8;
  if (inputText.length() > maxChars) {
    M5.Display.setTextSize(FONT_P);
  } else {
    M5.Display.setTextSize(FONT_M);
  }
  
  if (error != "") {
    M5.Display.drawString(error, WIDTH / 2, 39);
    delay(2000);
    drawInputField(inputText);
  } else {
    M5.Display.drawString(inputText, WIDTH / 2, 39);
  }
}

/***************************************************************************************
** Function name: drawKeyboard
** Description:   Draw the keyboard.
***************************************************************************************/
void drawKeyboard(String inputText, bool caps, int cursorX, int cursorY, int prevCursorX, int prevCursorY, bool refreshAll) {
  M5.Display.setTextSize(FONT_M);
  Serial.print("DRAWING KEYBOARD \n");
  
  // Calculate responsive button dimensions
  int btnGap = 2 * SCALE_FACTOR;
  int btnHeight = 20;
  int btnW1 = (WIDTH - (btnGap * 4)) / 5;  // Width for OK, CAP, DEL
  int btnW2 = btnW1 * 2;  // Width for SPACE (double)
  
  if ((prevCursorX == -1 && prevCursorY == -1) || refreshAll) {
    M5.Display.fillScreen(BGCOLOR);
    M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
    M5.Display.setTextSize(FONT_M);

    // Draw the OK, CAP, DEL & SPACE buttons with responsive layout
    M5.Display.drawRect(btnGap, 3, btnW1, btnHeight, COLOR_PRIMARY);
    M5.Display.drawRect(btnGap * 2 + btnW1, 3, btnW1, btnHeight, COLOR_PRIMARY);
    M5.Display.drawRect(btnGap * 3 + btnW1 * 2, 3, btnW1, btnHeight, COLOR_PRIMARY);
    M5.Display.drawRect(btnGap * 4 + btnW1 * 3, 3, btnW2, btnHeight, COLOR_PRIMARY);

    // Display the labels (button text)
    M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
    M5.Display.drawString("OK", btnGap + btnW1/2, 13);
    M5.Display.drawString("CAP", btnGap * 2 + btnW1 + btnW1/2, 13);
    M5.Display.drawString("DEL", btnGap * 3 + btnW1 * 2 + btnW1/2, 13);
    M5.Display.drawString("SPACE", btnGap * 4 + btnW1 * 3 + btnW2/2, 13);

    // Display the input value
    drawInputField(inputText);

    // Draw all the keys with responsive sizing
    int _x = WIDTH / 12;
    int _y = (HEIGHT - 54) / 4;
    int _xo = _x / 2 - 3;
    int _yo = (deviceConfig.type == DEVICE_M5CORE2) ? 6 : 0;  // Vertical offset for M5Core2
    
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 12; j++) {
        // Only show cursor on button navigation (M5Stick C Plus)
        if ((i == 0 && j == 0) && !refreshAll && deviceConfig.hasPhysicalButtons) {
          M5.Display.setTextColor(COLOR_ACCENT, BGCOLOR);
          M5.Display.drawRect(j * _x, i * _y + 54, _x, _y, COLOR_ACCENT);
        } else {
          M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
          M5.Display.drawRect(j * _x, i * _y + 54, _x, _y, COLOR_PRIMARY);
        }
        if (!caps) {
          M5.Display.drawChar(keys[i][j][0], (j * _x + _xo), (i * _y + 56 + _yo));
        } else {
          M5.Display.drawChar(keys[i][j][1], (j * _x + _xo), (i * _y + 56 + _yo));
        }
      }
    }
    if (refreshAll) {
      Serial.print("KEYBOARD REFRESH ALL \n");
      drawKeyboard(inputText, caps, cursorX, cursorY, prevCursorX - 1, prevCursorY - 1);
    }
  } else {
    // Redraw the old key if it has changed (only for physical button navigation)
    if (prevCursorX != cursorX || prevCursorY != cursorY) {
      int _x = WIDTH / 12;
      int _y = (HEIGHT - 54) / 4;
      int _xo = _x / 2 - 3;
      int _yo = (deviceConfig.type == DEVICE_M5CORE2) ? 6 : 0;  // Vertical offset for M5Core2

      // Redraw the old key
      if (prevCursorY < 4) {
        M5.Display.drawRect(prevCursorX * _x, prevCursorY * _y + 54, _x, _y, COLOR_PRIMARY);
        M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
        if (!caps) {
          M5.Display.drawChar(keys[prevCursorY][prevCursorX][0], (prevCursorX * _x + _xo), (prevCursorY * _y + 56 + _yo));
        } else {
          M5.Display.drawChar(keys[prevCursorY][prevCursorX][1], (prevCursorX * _x + _xo), (prevCursorY * _y + 56 + _yo));
        }
      } else {
        // Redraw the old TOP key
        int specialX = (prevCursorX == 0) ? btnGap : 
                       (prevCursorX == 1) ? btnGap * 2 + btnW1 : 
                       (prevCursorX == 2) ? btnGap * 3 + btnW1 * 2 : 
                       btnGap * 4 + btnW1 * 3;
        int textX = (prevCursorX == 0) ? btnGap + btnW1/2 : 
                    (prevCursorX == 1) ? btnGap * 2 + btnW1 + btnW1/2 : 
                    (prevCursorX == 2) ? btnGap * 3 + btnW1 * 2 + btnW1/2 : 
                    btnGap * 4 + btnW1 * 3 + btnW2/2;
        int rectangleWidth = (prevCursorX == 3) ? btnW2 : btnW1;
        M5.Display.drawRect(specialX, 3, rectangleWidth, btnHeight, COLOR_PRIMARY);
        M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
        M5.Display.drawString(specialKeys[prevCursorX], textX, 13);
      }

      // Draw the new selected key
      if (cursorY < 4) {
        M5.Display.drawRect(cursorX * _x, cursorY * _y + 54, _x, _y, COLOR_ACCENT);
        M5.Display.setTextColor(COLOR_ACCENT, BGCOLOR);
        if (!caps) {
          M5.Display.drawChar(keys[cursorY][cursorX][0], (cursorX * _x + _xo), (cursorY * _y + 56 + _yo));
        } else {
          M5.Display.drawChar(keys[cursorY][cursorX][1], (cursorX * _x + _xo), (cursorY * _y + 56 + _yo));
        }
      } else {
        // Draw the new selected TOP key
        int specialX = (cursorX == 0) ? btnGap : 
                       (cursorX == 1) ? btnGap * 2 + btnW1 : 
                       (cursorX == 2) ? btnGap * 3 + btnW1 * 2 : 
                       btnGap * 4 + btnW1 * 3;
        int textX = (cursorX == 0) ? btnGap + btnW1/2 : 
                    (cursorX == 1) ? btnGap * 2 + btnW1 + btnW1/2 : 
                    (cursorX == 2) ? btnGap * 3 + btnW1 * 2 + btnW1/2 : 
                    btnGap * 4 + btnW1 * 3 + btnW2/2;
        int rectangleWidth = (cursorX == 3) ? btnW2 : btnW1;
        M5.Display.drawRect(specialX, 3, rectangleWidth, btnHeight, COLOR_ACCENT);
        M5.Display.setTextColor(COLOR_ACCENT, BGCOLOR);
        M5.Display.drawString(specialKeys[cursorX], textX, 13);
      }
    }
  }
}

/***************************************************************************************
** Function name: handleKeyboardInput
** Description:   Handle the navigation between keys of the keyboard and actions.
***************************************************************************************/
void handleKeyboardInput() {
  static String inputText = "";
  static bool caps = false;
  static int cursorX = 0;
  static int cursorY = 0;
  static int prevCursorX = -1;
  static int prevCursorY = -1;
  static bool btnBWasPressed = false;  // Track if BtnB was pressed (to distinguish from hold)

  // Calculate keyboard dimensions
  int _x = WIDTH / 12;
  int _y = (HEIGHT - 54) / 4;
  int btnGap = 2 * SCALE_FACTOR;
  int btnHeight = 20;
  int btnW1 = (WIDTH - (btnGap * 4)) / 5;
  int btnW2 = btnW1 * 2;

  // M5Core2: Handle touch input directly on keys
  if (deviceConfig.hasTouchScreen) {
    static bool wasTouching = false;
    auto count = M5.Touch.getCount();
    
    if (count > 0 && !wasTouching) {
      wasTouching = true;
      auto t = M5.Touch.getDetail();
      int tx = t.x;
      int ty = t.y;
      Serial.printf("Keyboard touch: x=%d, y=%d\n", tx, ty);
      
      // Check if touch is on special buttons (OK, CAP, DEL, SPACE)
      if (ty >= 3 && ty <= 3 + btnHeight) {
        // OK button
        if (tx >= btnGap && tx <= btnGap + btnW1) {
          if ((hasMinLenToValidate && inputText.length() >= 8) || !hasMinLenToValidate) {
            isKeyboardOpen = false;
            renderList = true;
            inputValue = inputText;
            inputText = "";
            rectanglesRendered = false;
          } else if (hasMinLenToValidate && inputText.length() < 8) {
            drawInputField(inputText, "Min length: 8 char");
          }
          hasMinLenToValidate = false;
        }
        // CAP button
        else if (tx >= btnGap * 2 + btnW1 && tx <= btnGap * 2 + btnW1 * 2) {
          caps = !caps;
          drawKeyboard(inputText, caps, 0, 0, -1, -1, true);
        }
        // DEL button
        else if (tx >= btnGap * 3 + btnW1 * 2 && tx <= btnGap * 3 + btnW1 * 3) {
          if (inputText.length() > 0) {
            inputText.remove(inputText.length() - 1);
            drawInputField(inputText);
          }
        }
        // SPACE button
        else if (tx >= btnGap * 4 + btnW1 * 3 && tx <= btnGap * 4 + btnW1 * 3 + btnW2) {
          inputText += ' ';
          drawInputField(inputText);
        }
      }
      // Check if touch is on keyboard keys
      else if (ty >= 54 && ty < 54 + _y * 4) {
        int keyX = tx / _x;
        int keyY = (ty - 54) / _y;
        
        if (keyX >= 0 && keyX < 12 && keyY >= 0 && keyY < 4) {
          char selectedKey = caps ? keys[keyY][keyX][1] : keys[keyY][keyX][0];
          inputText += selectedKey;
          drawInputField(inputText);
        }
      }
    } else if (count == 0) {
      wasTouching = false;
    }
  }
  // M5Stick C Plus: Handle button navigation
  else if (deviceConfig.hasPhysicalButtons) {
    // Draw the keyboard, only if cursor position has changed
    if ((prevCursorX != cursorX || prevCursorY != cursorY) && prevCursorX != -1) {
      drawKeyboard(inputText, caps, cursorX, cursorY, prevCursorX, prevCursorY);
      prevCursorX = cursorX;
      prevCursorY = cursorY;
    }

    // Handle horizontal navigation - distinguish between short press (RIGHT) and long press (LEFT)
    if (M5.BtnB.wasPressed()) {
      btnBWasPressed = true;  // Mark that button was pressed
    }
    
    if (M5.BtnB.wasHold()) {
      // Long press - navigate LEFT
      btnBWasPressed = false;  // Clear flag, this was a hold
      prevCursorX = cursorX;
      prevCursorY = cursorY;

      cursorX--;
      if (cursorX < 0) {
        if (cursorY < 4) {
          cursorX = 11;
        } else {
          cursorX = 3;
        }
      }
    }
    else if (btnBWasPressed && !M5.BtnB.isPressed()) {
      // Button was pressed and now released (without being held) - navigate RIGHT
      btnBWasPressed = false;  // Clear flag
      prevCursorX = cursorX;
      prevCursorY = cursorY;

      cursorX++;
      if (cursorY < 4 && cursorX > 11) {
        cursorX = 0;
      } else if (cursorY == 4 && cursorX > 3) {
        cursorX = 0;
      }
    }

    // Navigate to the TOP keys
    if (M5.BtnPWR.wasHold()) {
      prevCursorX = cursorX;
      prevCursorY = cursorY;
      cursorX = 0;
      cursorY = 4;
    }

    // Navigate between the keys vertically
    if (M5.BtnPWR.wasPressed()) {
      prevCursorX = cursorX;
      prevCursorY = cursorY;

      cursorY++;
      if (cursorY > 3) {
        cursorY = 0;
      }
    }

    if (M5.BtnA.wasPressed()) {
      // TOP keys actions
      if (cursorY == 4) {
        if (cursorX == 0) { // OK
          if ((hasMinLenToValidate && inputText.length() >= 8) || !hasMinLenToValidate) {
            cursorY = 0;
            isKeyboardOpen = false;
            renderList = true;
            inputValue = inputText;
            inputText = "";
            rectanglesRendered = false;
          } else if (hasMinLenToValidate && inputText.length() < 8) {
            drawInputField(inputText, "Min length: 8 char");
          }
          hasMinLenToValidate = false;
        } else if (cursorX == 1) { // CAP
          caps = !caps;
          drawKeyboard(inputText, caps, cursorX, cursorY, prevCursorX, prevCursorY, true);
        } else if (cursorX == 2) { // DEL
          if (inputText.length() > 0) {
            inputText.remove(inputText.length() - 1);
          }
        } else if (cursorX == 3) { // SPACE
          inputText += ' ';
        }
      } else {
        char selectedKey = caps ? keys[cursorY][cursorX][1] : keys[cursorY][cursorX][0];
        inputText += selectedKey;
      }
      drawInputField(inputText);
    }
  }
}
