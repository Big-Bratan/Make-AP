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
  // Calculate responsive dimensions
  int margin = 5 * SCALE_FACTOR;
  int headerHeight = 30;
  int listY = 37;
  int btnHeight = 30;
  int btnMargin = 2;
  // M5Core2: fill space between header and bottom buttons (240 - 37 - 30 - 2 - 5 = 166)
  int listHeight = (deviceConfig.type == DEVICE_M5CORE2) ? 
                   HEIGHT - listY - btnHeight - btnMargin - 5 : 95;
  int titleX = 15 * SCALE_FACTOR;
  
  // Position image with appropriate right margin based on device
  int imgMarginRight = (deviceConfig.type == DEVICE_M5CORE2) ? 20 : 10;
  int imgX = WIDTH - IMG_SIZE - imgMarginRight;

  if (!rectanglesRendered) {
    // Clear screen
    M5.Display.fillScreen(TFT_BLACK);
    M5.Display.setTextSize(FONT_P);
    M5.Lcd.drawRoundRect(margin, 5, WIDTH - (margin * 2), headerHeight, 5, COLOR_PRIMARY);
    M5.Lcd.drawRoundRect(margin, listY, WIDTH - (margin * 2), listHeight, 5, COLOR_PRIMARY);
    drawBatteryStatus();
    
    // Draw button guide for M5Core2
    if (deviceConfig.type == DEVICE_M5CORE2) {
      drawButtonGuide();
    }
    
    // To avoid re-rendering rectangle frames
    rectanglesRendered = true;
  }

  // Re-render the image only if it has changed or if it's another list
  const uint16_t *newImage = (selectedIndex == 0) ? keyboardImg : fileImg;
  if (newImage != currentImage || currentTitle != String(title)) {
    // Position image higher in the content area (between header and buttons)
    int contentCenterY = (listY + (listY + listHeight)) / 2;  // Center of content area
    int imgY = contentCenterY - IMG_SIZE / 2 - 10;  // Shift up by 10px
    
    // Clear previous image area (careful not to clear borders)
    // M5Core2: extend 5px left, 5px top/bottom
    // M5StickC: extend 2px left, 2px top/bottom to avoid erasing yellow border
    int clearPadding = (deviceConfig.type == DEVICE_M5CORE2) ? 5 : 2;
    int clearWidth = IMG_SIZE + clearPadding;  // Only extend left, not to the right
    int clearHeight = IMG_SIZE + (clearPadding * 2);  // Extend top and bottom
    M5.Display.fillRect(imgX - clearPadding, imgY - clearPadding, clearWidth, clearHeight, TFT_BLACK);
    // Draw new image
    M5.Lcd.pushImage(imgX, imgY, IMG_SIZE, IMG_SIZE, newImage);
    currentImage = newImage;
  }

  // Re-render the title only if it has changed
  if (currentTitle != String(title)) {
    currentTitle = String(title);
    M5.Display.setCursor(titleX, 21);
    M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Display.fillRect(10 * SCALE_FACTOR, 20, WIDTH / 2, 8, TFT_BLACK);
    M5.Display.print(currentTitle);
  }

  // Re-render the list if changed
  // Limit display width to not overlap with image
  int maxTextWidth = (deviceConfig.type == DEVICE_M5CORE2) ? imgX - 20 : WIDTH - 20;
  int listMarginTop = (deviceConfig.type == DEVICE_M5CORE2) ? 12 : 0;  // Top margin for M5Core2 only
  
  for (int i = 0; i < itemCount; ++i) {
    if (i == selectedIndex) {
      // Cursor color
      M5.Display.setTextColor(TFT_WHITE, COLOR_ACCENT);
    } else {
      // Default color
      M5.Display.setTextColor(TFT_WHITE, TFT_BLACK);
    }

    M5.Display.setCursor(titleX, 50 + listMarginTop + i * 20);
    
    // Truncate text if needed
    String itemText = String(list[i]);
    if (M5.Display.textWidth(itemText) > maxTextWidth - titleX) {
      while (M5.Display.textWidth(itemText + "...") > maxTextWidth - titleX && itemText.length() > 0) {
        itemText.remove(itemText.length() - 1);
      }
      itemText += "...";
    }
    M5.Display.print(itemText);
  }
}

/***************************************************************************************
** Function name: drawAP
** Description:   Display the AP view.
***************************************************************************************/
void drawAP() {
  // Calculate responsive dimensions
  int margin = 5 * SCALE_FACTOR;
  int textX = 15 * SCALE_FACTOR;
  
  // Position image with appropriate right margin based on device
  int imgMarginRight = (deviceConfig.type == DEVICE_M5CORE2) ? 20 : 10;
  int imgX = WIDTH - IMG_SIZE - imgMarginRight;
  
  int btnHeight = 30;
  int btnMargin = 2;
  // M5Core2: fill space between header and bottom buttons
  int boxHeight = (deviceConfig.type == DEVICE_M5CORE2) ? 
                  HEIGHT - 5 - btnHeight - btnMargin - 5 : HEIGHT - 10;
  
  M5.Display.fillScreen(TFT_BLACK);
  drawBatteryStatus();
  M5.Lcd.drawRoundRect(margin, 5, WIDTH - (margin * 2), boxHeight, 5, COLOR_PRIMARY);
  
  // Draw button guide for M5Core2 with "RESTART" label
  if (deviceConfig.type == DEVICE_M5CORE2) {
    int btnMarginSide = 10;  // Left and right padding for buttons
    int btnGap = 5;          // Gap between buttons
    int btnY = HEIGHT - btnHeight - btnMargin;  // Position at bottom
    int btnWidth = (WIDTH - 2 * btnMarginSide - 2 * btnGap) / 3;
    
    // Draw center button only (restart) - use same calculation as drawButtonGuide
    int btn2X = btnMarginSide + btnWidth + btnGap;
    M5.Lcd.drawRoundRect(btn2X, btnY, btnWidth, btnHeight, 3, COLOR_PRIMARY);
    M5.Display.setTextSize(FONT_P);
    M5.Display.setTextColor(COLOR_PRIMARY, TFT_BLACK);
    M5.Display.drawString("RESTART", btn2X + btnWidth / 2, btnY + btnHeight / 2);
  }
  
  M5.Display.setTextColor(TFT_WHITE);
  M5.Display.setCursor(textX, HEIGHT / 2 - 5);
  M5.Display.print("Starting AP...");

  WiFi.softAP(selectedSSID.c_str(), selectedPassword.c_str());
  creatingAP = true;
  // Wait for the AP to be started
  delay(1000);

  // Refresh screen - clear info area but not button guide
  int clearHeight = (deviceConfig.type == DEVICE_M5CORE2) ? boxHeight - 20 : HEIGHT - 35;
  M5.Display.fillRect(10 * SCALE_FACTOR, 20, WIDTH / 2 + (15 * SCALE_FACTOR), clearHeight, TFT_BLACK);
  
  // Position router image higher in the content area
  int contentAreaHeight = boxHeight;
  int imgY = (contentAreaHeight / 2) - IMG_SIZE / 2 - 10;  // Shift up by 10px
  // Add top margin for M5StickC Plus2
  int routerMarginTop = (deviceConfig.type == DEVICE_M5CORE2) ? 0 : 15;
  imgY += routerMarginTop;
  M5.Lcd.pushImage(imgX, imgY, IMG_SIZE, IMG_SIZE, routerImg);

  // Top margin for AP info (M5Core2 only)
  int infoMarginTop = (deviceConfig.type == DEVICE_M5CORE2) ? 15 : 0;

  // IP SECTION
  M5.Display.setCursor(textX, 28 + infoMarginTop);
  IPAddress IP = WiFi.softAPIP();
  M5.Display.setTextSize(FONT_XS);
  M5.Display.print("IP:");
  M5.Display.setCursor(textX, 43 + infoMarginTop);
  M5.Display.setTextSize(FONT_P);
  M5.Display.print(IP);

  // SSID SECTION
  M5.Display.setCursor(textX, 62 + infoMarginTop);
  M5.Display.setTextSize(FONT_XS);
  M5.Display.print("SSID:");
  M5.Display.setCursor(textX, 77 + infoMarginTop);
  M5.Display.setTextSize(FONT_P);
  M5.Display.print(selectedSSID);

  // PASSWORD SECTION
  M5.Display.setCursor(textX, 96 + infoMarginTop);
  M5.Display.setTextSize(FONT_XS);
  M5.Display.print("Password:");
  M5.Display.setCursor(textX, 111 + infoMarginTop);
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
  int marginRight = deviceConfig.type == DEVICE_M5CORE2 ? 10 : 0;
  M5.Lcd.drawRoundRect(WIDTH - 42 - marginRight, 10, 30, 17, 2, COLOR_PRIMARY);
  int bat = getBattery();
  M5.Lcd.setTextSize(FONT_P);
  M5.Lcd.setTextColor(COLOR_PRIMARY, BLACK);
  M5.Lcd.drawRightString("  " + String(bat) + "%", WIDTH - 45 - marginRight, 14, 1);
  M5.Lcd.fillRoundRect(WIDTH - 40 - marginRight, 12, 28, 12, 2, BLACK);
  // Battery percentage bar
  M5.Lcd.fillRoundRect(WIDTH - 40 - marginRight, 12, 26 * bat / 100, 13, 2, COLOR_PRIMARY);
  // Battery tip
  M5.Lcd.fillRoundRect(WIDTH - 12 - marginRight, 15, 2, 6, 2, COLOR_PRIMARY);
  // Vertical separators
  M5.Lcd.drawLine(WIDTH - 32 - marginRight, 11, WIDTH - 32 - marginRight, 11 + 14, BLACK);
  M5.Lcd.drawLine(WIDTH - 22 - marginRight, 11, WIDTH - 22 - marginRight, 11 + 14, BLACK);
}

/***************************************************************************************
** Function name: drawButtonGuide
** Description:   Draw the bottom button guide (M5Core2 only)
***************************************************************************************/
void drawButtonGuide() {
  if (deviceConfig.type != DEVICE_M5CORE2) return;
  
  int margin = 10;         // Left and right padding
  int gap = 5;             // Gap between buttons
  int btnHeight = 30;
  int btnY = HEIGHT - btnHeight - 2;  // Position at bottom of screen with 2px margin
  
  // Calculate button width: (total width - 2*margin - 2*gaps) / 3 buttons
  int btnWidth = (WIDTH - 2 * margin - 2 * gap) / 3;
  
  // Draw three button zones with yellow borders
  // Left button (UP)
  int btn1X = margin;
  M5.Lcd.drawRoundRect(btn1X, btnY, btnWidth, btnHeight, 3, COLOR_PRIMARY);
  M5.Display.setTextSize(FONT_P);
  M5.Display.setTextColor(COLOR_PRIMARY, TFT_BLACK);
  M5.Display.drawString("UP", btn1X + btnWidth / 2, btnY + btnHeight / 2);
  
  // Center button (SELECT)
  int btn2X = margin + btnWidth + gap;
  M5.Lcd.drawRoundRect(btn2X, btnY, btnWidth, btnHeight, 3, COLOR_PRIMARY);
  M5.Display.drawString("SELECT", btn2X + btnWidth / 2, btnY + btnHeight / 2);
  
  // Right button (DOWN)
  int btn3X = margin + 2 * btnWidth + 2 * gap;
  M5.Lcd.drawRoundRect(btn3X, btnY, btnWidth, btnHeight, 3, COLOR_PRIMARY);
  M5.Display.drawString("DOWN", btn3X + btnWidth / 2, btnY + btnHeight / 2);
}
