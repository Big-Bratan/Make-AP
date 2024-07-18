#include <WiFi.h>
#include "Display.h"

bool rectanglesRendered = false;
const uint16_t *currentImage = nullptr;
String currentTitle = "";

/***************************************************************************************
** Function name: displayList
** Description:   Display the current list: SSID or PASSWORD.
***************************************************************************************/
void displayList(const char *title, const char *list[], int itemCount) {

  if (!rectanglesRendered) {
    // Clear screen
    M5.Display.fillScreen(TFT_BLACK);
    M5.Display.setTextSize(FONT_P);
    M5.Lcd.drawRoundRect(5, 5, WIDTH - 10, 30, 5, COLOR_PRIMARY);
    M5.Lcd.drawRoundRect(5, 37, WIDTH - 10, 95, 5, COLOR_PRIMARY);
    drawBatteryStatus();
    // To avoid re-rendering rectangle frames
    rectanglesRendered = true;
  }

  // Re-render the image only if it has change or if it's another list
  const uint16_t *newImage = (selectedIndex == 0) ? keyboardImg : fileImg;
  if (newImage != currentImage || currentTitle != String(title)) {
    M5.Lcd.pushImage(WIDTH - 84, HEIGHT / 2 - IMG_SIZE / 3, IMG_SIZE, IMG_SIZE, newImage);
    currentImage = newImage;
  }

  // Re-render the title only if it has changed
  if (currentTitle != String(title)) {
    currentTitle = String(title);
    M5.Display.setCursor(15, 21);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Display.fillRect(10, 20, WIDTH / 2, 8, TFT_BLACK);
    M5.Display.print(currentTitle);
  }

  // Re-render the list if changed
  for (int i = 0; i < itemCount; ++i) {
    if (i == selectedIndex) {
      // Cursor color
      M5.Display.setTextColor(TFT_WHITE, COLOR_ACCENT);
    } else {
      // Default color
      M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    }

    M5.Display.setCursor(15, 50 + i * 20);
    M5.Display.print(list[i]);
  }
}

/***************************************************************************************
** Function name: drawAP
** Description:   Display the AP view.
***************************************************************************************/
void drawAP() {
  M5.Display.fillScreen(TFT_BLACK);
  drawBatteryStatus();
  M5.Lcd.drawRoundRect(5, 5, WIDTH - 10, HEIGHT - 10, 5, COLOR_PRIMARY);
  M5.Display.setTextColor(TFT_WHITE);
  M5.Display.setCursor(15, HEIGHT / 2 - 5);
  M5.Display.print("Starting AP...");

  WiFi.softAP(selectedSSID.c_str(), selectedPassword.c_str());
  creatingAP = true;
  // Wait for the AP to be started
  delay(1000);

  // Refresh screen
  M5.Display.fillRect(10, 20, WIDTH / 2 + 15, HEIGHT - 35, TFT_BLACK);
  M5.Lcd.pushImage(WIDTH - 84, HEIGHT / 2 - IMG_SIZE / 2, IMG_SIZE, IMG_SIZE, routerImg);

  // IP SECTION
  M5.Display.setCursor(15, 28);
  IPAddress IP = WiFi.softAPIP();
  M5.Display.setTextSize(FONT_XS);
  M5.Display.print("IP:");
  M5.Display.setCursor(15, 43);
  M5.Display.setTextSize(FONT_P);
  M5.Display.print(IP);

  // SSID SECTION
  M5.Display.setCursor(15, 62);
  M5.Display.setTextSize(FONT_XS);
  M5.Display.print("SSID:");
  M5.Display.setCursor(15, 77);
  M5.Display.setTextSize(FONT_P);
  M5.Display.print(selectedSSID);

  // PASSWORD SECTION
  M5.Display.setCursor(15, 96);
  M5.Display.setTextSize(FONT_XS);
  M5.Display.print("Password:");
  M5.Display.setCursor(15, 111);
  M5.Display.setTextSize(FONT_P);
  M5.Display.print(selectedPassword);
}

/***************************************************************************************
** Function name: resetDisplay
** Description:   Ret cursor to 0,0, screen and text to default color
***************************************************************************************/
void resetDisplay(int x, int y, uint16_t fc, int size, uint16_t bg, uint16_t screen) {
  M5.Display.setCursor(x, y);
  M5.Display.fillScreen(screen);
  M5.Display.setTextSize(size);
  M5.Display.setTextColor(fc, bg);
}

/***************************************************************************************
** Function name: getBattery
** Description:   Get the battery level in percent.
***************************************************************************************/
double getBattery(void) {
  float percent = M5.Power.getBatteryLevel();
  return (percent < 0) ? 0 : (percent >= 100) ? 100 : percent;
}

/***************************************************************************************
** Function name: drawBatteryStatus
** Description:   Draw the battery level (int) and visualization.
***************************************************************************************/
void drawBatteryStatus() {
  M5.Lcd.drawRoundRect(WIDTH - 42, 10, 30, 17, 2, COLOR_PRIMARY);
  int bat = getBattery();
  M5.Lcd.setTextSize(FONT_P);
  M5.Lcd.setTextColor(COLOR_PRIMARY, BLACK);
  M5.Lcd.drawRightString("  " + String(bat) + "%", WIDTH - 45, 14, 1);
  M5.Lcd.fillRoundRect(WIDTH - 40, 12, 28, 12, 2, BLACK);
  // Battery percentage bar
  M5.Lcd.fillRoundRect(WIDTH - 40, 12, 26 * bat / 100, 13, 2, COLOR_PRIMARY);
  // Battery tip
  M5.Lcd.fillRoundRect(WIDTH - 12, 15, 2, 6, 2, COLOR_PRIMARY);
  // Vertical separators
  M5.Lcd.drawLine(WIDTH - 32, 11, WIDTH - 32, 11 + 14, BLACK);
  M5.Lcd.drawLine(WIDTH - 22, 11, WIDTH - 22, 11 + 14, BLACK);
}
