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
  // Erase & redraw input field
  M5.Display.fillRect(3, 27, M5.Display.width() - 6, 23, BGCOLOR);
  M5.Display.drawRect(3, 27, M5.Display.width() - 6, 23, COLOR_PRIMARY);
  M5.Display.setTextColor(TFT_WHITE, BGCOLOR);

  int xPosition = 20;

  // Adjust text size depending on its length
  if (inputText.length() > 8) {
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
  if ((prevCursorX == -1 && prevCursorY == -1) || refreshAll) {
    M5.Display.fillScreen(BGCOLOR);
    M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
    M5.Display.setTextSize(FONT_M);

    // Draw the OK, CAP, DEL & SPACE buttons
    M5.Display.drawRect(3, 3, 50, 20, COLOR_PRIMARY);
    M5.Display.drawRect(55, 3, 50, 20, COLOR_PRIMARY);
    M5.Display.drawRect(107, 3, 50, 20, COLOR_PRIMARY);
    M5.Display.drawRect(159, 3, 78, 20, COLOR_PRIMARY);

    // Display the labels (button text)
    M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
    M5.Display.drawString("OK", 24, 13);
    M5.Display.drawString("CAP", 80, 13);
    M5.Display.drawString("DEL", 131, 13);
    M5.Display.drawString("SPACE", 196, 13);

    // Display the input value
    drawInputField(inputText);

    // Draw all the keys
    int _x = M5.Display.width() / 12;
    int _y = (M5.Display.height() - 54) / 4;
    int _xo = _x / 2 - 3;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 12; j++) {
        if ((i == 0 && j == 0) && !refreshAll) {
          M5.Display.setTextColor(COLOR_ACCENT, BGCOLOR);
          M5.Display.drawRect(j * _x, i * _y + 54, _x, _y, COLOR_ACCENT);
        } else {
          M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
          M5.Display.drawRect(j * _x, i * _y + 54, _x, _y, COLOR_PRIMARY);
        }
        if (!caps) {
          M5.Display.drawChar(keys[i][j][0], (j * _x + _xo), (i * _y + 56));
        } else {
          M5.Display.drawChar(keys[i][j][1], (j * _x + _xo), (i * _y + 56));
        }
      }
    }
    if (refreshAll) {
      Serial.print("KEYBOARD REFRESH ALL \n");
      drawKeyboard(inputText, caps, cursorX, cursorY, prevCursorX - 1, prevCursorY - 1);
    }
  } else {
    // Redraw the old key if it has changed
    if (prevCursorX != cursorX || prevCursorY != cursorY) {
      int _x = M5.Display.width() / 12;
      int _y = (M5.Display.height() - 54) / 4;
      int _xo = _x / 2 - 3;

      // Redraw the old key
      if (prevCursorY < 4) {
        M5.Display.drawRect(prevCursorX * _x, prevCursorY * _y + 54, _x, _y, COLOR_PRIMARY);
        M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
        if (!caps) {
          M5.Display.drawChar(keys[prevCursorY][prevCursorX][0], (prevCursorX * _x + _xo), (prevCursorY * _y + 56));
        } else {
          M5.Display.drawChar(keys[prevCursorY][prevCursorX][1], (prevCursorX * _x + _xo), (prevCursorY * _y + 56));
        }
      } else {
        // Redraw the old TOP key
        int specialX = (prevCursorX == 0) ? 3 : (prevCursorX == 1) ? 55 : (prevCursorX == 2) ? 107 : 159;
        int textX = (prevCursorX == 0) ? 24 : (prevCursorX == 1) ? 80 : (prevCursorX == 2) ? 131 : 196;
        int rectangleWidth = (prevCursorX == 3) ? 78 : 50;
        M5.Display.drawRect(specialX, 3, rectangleWidth, 20, COLOR_PRIMARY);
        M5.Display.setTextColor(TFT_WHITE, BGCOLOR);
        M5.Display.drawString(specialKeys[prevCursorX], textX, 13);
      }

      // Draw the new selected key
      if (cursorY < 4) {
        M5.Display.drawRect(cursorX * _x, cursorY * _y + 54, _x, _y, COLOR_ACCENT);
        M5.Display.setTextColor(COLOR_ACCENT, BGCOLOR);
        if (!caps) {
          M5.Display.drawChar(keys[cursorY][cursorX][0], (cursorX * _x + _xo), (cursorY * _y + 56));
        } else {
          M5.Display.drawChar(keys[cursorY][cursorX][1], (cursorX * _x + _xo), (cursorY * _y + 56));
        }
      } else {
        // Draw the new selected TOP key
        int specialX = (cursorX == 0) ? 3 : (cursorX == 1) ? 55 : (cursorX == 2) ? 107 : 159;
        int textX = (cursorX == 0) ? 24 : (cursorX == 1) ? 80 : (cursorX == 2) ? 131 : 196;
        int rectangleWidth = (cursorX == 3) ? 78 : 50;
        M5.Display.drawRect(specialX, 3, rectangleWidth, 20, COLOR_ACCENT);
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

  // Draw the keyboard, only if cursor position has changed
  if ((prevCursorX != cursorX || prevCursorY != cursorY) && prevCursorX != -1) {
    drawKeyboard(inputText, caps, cursorX, cursorY, prevCursorX, prevCursorY);
    prevCursorX = cursorX;
    prevCursorY = cursorY;
  }

  // Navigate between the keys horizontaly
  if (M5.BtnB.wasPressed()) {
    prevCursorX = cursorX; // Keep old position before changing it
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
    cursorX = 0;
    cursorY = 4;
  }

  // Navigate between the keys verticaly
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
          drawInputField(inputText, "Min lenght: 8 char");
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
