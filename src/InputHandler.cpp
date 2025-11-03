#include "InputHandler.h"

InputHandler input;

/***************************************************************************************
** Function name: begin
** Description:   Initialize input handler
***************************************************************************************/
void InputHandler::begin() {
  touchZoneCount = 0;
  touchZonesEnabled = false;
  wasTouched = false;
  lastTouchedButton = BTN_NONE;
}

/***************************************************************************************
** Function name: update
** Description:   Update input state (call this in loop)
***************************************************************************************/
void InputHandler::update() {
  // Note: M5.update() is called in main loop, not here!
  // Calling it twice would clear the wasPressed() state
  
  // Handle custom touch zones for keyboard/other UI (M5Core2 only)
  if (deviceConfig.hasTouchScreen && touchZonesEnabled) {
    auto count = M5.Touch.getCount();
    
    if (count > 0 && !wasTouched) {
      auto detail = M5.Touch.getDetail();
      int tx = detail.x;
      int ty = detail.y;
      
      wasTouched = true;
      touchStartTime = millis();
      lastTouchedButton = getTouchedZone(tx, ty);
    } else if (count == 0 && wasTouched) {
      // Touch was released
      wasTouched = false;
    }
  }
}

/***************************************************************************************
** Function name: wasSelectPressed
** Description:   Check if select button was pressed (BtnB for M5Core2, BtnA for M5Stick)
***************************************************************************************/
bool InputHandler::wasSelectPressed() {
  if (deviceConfig.type == DEVICE_M5CORE2) {
    // M5Core2: BtnB is the center button (SELECT)
    return M5.BtnB.wasPressed();
  } else if (deviceConfig.hasPhysicalButtons) {
    // M5StickC Plus: BtnA is the main button (SELECT)
    return M5.BtnA.wasPressed();
  }
  
  // Check custom touch zones for keyboard
  if (touchZonesEnabled && lastTouchedButton == BTN_SELECT && !wasTouched) {
    lastTouchedButton = BTN_NONE;
    return true;
  }
  
  return false;
}

/***************************************************************************************
** Function name: wasUpPressed
** Description:   Check if up button was pressed (BtnA for M5Core2, BtnPWR for M5Stick)
***************************************************************************************/
bool InputHandler::wasUpPressed() {
  if (deviceConfig.type == DEVICE_M5CORE2) {
    // M5Core2: BtnA is the left button (UP)
    return M5.BtnA.wasPressed();
  } else if (deviceConfig.hasPhysicalButtons) {
    // M5StickC Plus: BtnPWR is the power button (UP)
    return M5.BtnPWR.wasPressed();
  }
  
  // Check custom touch zones for keyboard
  if (touchZonesEnabled && lastTouchedButton == BTN_UP && !wasTouched) {
    lastTouchedButton = BTN_NONE;
    return true;
  }
  
  return false;
}

/***************************************************************************************
** Function name: wasDownPressed
** Description:   Check if down button was pressed (BtnC for M5Core2, BtnB for M5Stick)
***************************************************************************************/
bool InputHandler::wasDownPressed() {
  if (deviceConfig.type == DEVICE_M5CORE2) {
    // M5Core2: BtnC is the right button (DOWN)
    return M5.BtnC.wasPressed();
  } else if (deviceConfig.hasPhysicalButtons) {
    // M5StickC Plus: BtnB is the side button (DOWN)
    return M5.BtnB.wasPressed();
  }
  
  // Check custom touch zones for keyboard
  if (touchZonesEnabled && lastTouchedButton == BTN_DOWN && !wasTouched) {
    lastTouchedButton = BTN_NONE;
    return true;
  }
  
  return false;
}

/***************************************************************************************
** Function name: wasVerticalPressed
** Description:   Check if vertical nav button was pressed (BtnPWR or touch zone)
***************************************************************************************/
bool InputHandler::wasVerticalPressed() {
  if (deviceConfig.hasPhysicalButtons) {
    return M5.BtnPWR.wasPressed();
  } else if (touchZonesEnabled) {
    if (lastTouchedButton == BTN_VERTICAL && !wasTouched) {
      lastTouchedButton = BTN_NONE;
      return true;
    }
  }
  return false;
}

/***************************************************************************************
** Function name: wasVerticalHeld
** Description:   Check if vertical nav button was held (BtnPWR hold or long touch)
***************************************************************************************/
bool InputHandler::wasVerticalHeld() {
  if (deviceConfig.hasPhysicalButtons) {
    return M5.BtnPWR.wasHold();
  } else if (touchZonesEnabled && wasTouched) {
    if (lastTouchedButton == BTN_VERTICAL && 
        (millis() - touchStartTime) > 500) {
      return true;
    }
  }
  return false;
}

/***************************************************************************************
** Function name: isTouching
** Description:   Check if screen is currently being touched
***************************************************************************************/
bool InputHandler::isTouching() {
  if (deviceConfig.hasTouchScreen) {
    return M5.Touch.getCount() > 0;
  }
  return false;
}

/***************************************************************************************
** Function name: getTouchPoint
** Description:   Get current touch coordinates
***************************************************************************************/
void InputHandler::getTouchPoint(int &x, int &y) {
  if (deviceConfig.hasTouchScreen) {
    auto t = M5.Touch.getDetail();
    x = t.x;
    y = t.y;
  }
}

/***************************************************************************************
** Function name: addTouchZone
** Description:   Add a touch zone for M5Core2
***************************************************************************************/
void InputHandler::addTouchZone(int x, int y, int w, int h, VirtualButton btn) {
  if (touchZoneCount < 10) {
    touchZones[touchZoneCount] = {x, y, w, h, btn, true};
    touchZoneCount++;
  }
}

/***************************************************************************************
** Function name: clearTouchZones
** Description:   Clear all touch zones
***************************************************************************************/
void InputHandler::clearTouchZones() {
  touchZoneCount = 0;
}

/***************************************************************************************
** Function name: enableTouchZones
** Description:   Enable/disable touch zone detection
***************************************************************************************/
void InputHandler::enableTouchZones(bool enable) {
  touchZonesEnabled = enable;
}

/***************************************************************************************
** Function name: getTouchedZone
** Description:   Determine which zone was touched
***************************************************************************************/
VirtualButton InputHandler::getTouchedZone(int x, int y) {
  for (int i = 0; i < touchZoneCount; i++) {
    if (touchZones[i].active &&
        x >= touchZones[i].x && 
        x <= touchZones[i].x + touchZones[i].width &&
        y >= touchZones[i].y && 
        y <= touchZones[i].y + touchZones[i].height) {
      return touchZones[i].button;
    }
  }
  return BTN_NONE;
}

