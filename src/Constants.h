#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <M5Unified.h>
#include "File.h"
#include "KeyboardImg.h"
#include "Router.h"

extern bool isKeyboardOpen;
extern bool renderList;
extern bool creatingAP;
extern bool rectanglesRendered;
extern String inputValue;
extern String selectedSSID;
extern String selectedPassword;
extern int selectedIndex;

#define FONT_XS 1
#define FONT_P 1.5
#define FONT_M 2
#define FONT_G 3
#define MAX_MENU_SIZE 5
#define MAX_ITEMS 10
#define LH 8
#define LW 6
#define IMG_SIZE 64

#define COLOR_WHITE TFT_WHITE
#define COLOR_BLACK TFT_BLACK
#define COLOR_RED TFT_RED
#define COLOR_GREEN TFT_GREEN
#define COLOR_BLUE TFT_BLUE
#define COLOR_PRIMARY 0xF7D4 //0xA30A
#define COLOR_ACCENT 0x80a4
#define BGCOLOR TFT_BLACK
#define FGCOLOR 0x8417


///

#define ROTATION 1
#define WIDTH M5.Lcd.width()
#define HEIGHT M5.Lcd.height()



#endif // CONSTANTS_H