#ifndef DISPLAY_H
#define DISPLAY_H

#include "Constants.h"
#include <vector>

void resetDisplay(int x = 0, int y = 0, uint16_t fc = FGCOLOR, int size = FONT_M, uint16_t bg = BGCOLOR, uint16_t screen = BGCOLOR);
void displayList(const char* title, const char* list[], int itemCount);
void drawBatteryStatus();
void drawAP();
void drawAPWithServeButton();
void drawButtonGuide();
void drawServeFileButton();
void displayFileList(std::vector<String>& files, bool fullRedraw = true);
void drawServingStatus(String filename);

#endif // DISPLAY_H
