#ifndef DISPLAY_H
#define DISPLAY_H

#include "Constants.h"

void resetDisplay(int x = 0, int y = 0, uint16_t fc = FGCOLOR, int size = FONT_M, uint16_t bg = BGCOLOR, uint16_t screen = BGCOLOR);
void displayList(const char* title, const char* list[], int itemCount);
void drawBatteryStatus();
void drawAP();
void drawButtonGuide();

#endif // DISPLAY_H
