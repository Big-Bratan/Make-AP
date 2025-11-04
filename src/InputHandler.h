#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <M5Unified.h>
#include "DeviceConfig.h"

// Virtual button identifiers
enum VirtualButton {
  BTN_NONE,
  BTN_SELECT,     // Select/OK (was BtnA / M5Core2 center button)
  BTN_UP,         // Navigate up (M5Core2 left button)
  BTN_DOWN,       // Navigate down (was BtnB / M5Core2 right button)
  BTN_VERTICAL    // Vertical navigation (was BtnPWR)
};

// Touch zone definition
struct TouchZone {
  int x, y, width, height;
  VirtualButton button;
  bool active;
};

class InputHandler {
public:
  void begin();
  void update();
  
  // Unified button interface (works for both touch and physical buttons)
  bool wasSelectPressed();
  bool wasUpPressed();      // M5Core2 left button / M5Stick PWR
  bool wasDownPressed();    // M5Core2 right button / M5Stick BtnB
  bool wasVerticalPressed();
  bool wasVerticalHeld();
  
  // Touch-specific methods
  bool isTouching();
  void getTouchPoint(int &x, int &y);
  
  // Touch zone management for M5Core2
  void addTouchZone(int x, int y, int w, int h, VirtualButton btn);
  void clearTouchZones();
  void enableTouchZones(bool enable);
  
private:
  TouchZone touchZones[10];
  int touchZoneCount = 0;
  bool touchZonesEnabled = false;
  
  // Touch state tracking
  bool wasTouched = false;
  unsigned long touchStartTime = 0;
  VirtualButton lastTouchedButton = BTN_NONE;
  
  // Check which touch zone was touched
  VirtualButton getTouchedZone(int x, int y);
};

extern InputHandler input;

#endif // INPUTHANDLER_H

