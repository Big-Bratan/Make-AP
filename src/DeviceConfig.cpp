#include "DeviceConfig.h"

DeviceConfig deviceConfig;

/***************************************************************************************
** Function name: initDeviceConfig
** Description:   Detect device type and set configuration
***************************************************************************************/
void initDeviceConfig() {
  auto board = M5.getBoard();
  
  deviceConfig.screenWidth = M5.Display.width();
  deviceConfig.screenHeight = M5.Display.height();
  
  // Detect device based on board type
  if (board == m5::board_t::board_M5StickCPlus) {
    deviceConfig.type = DEVICE_M5STICK_CPLUS;
    deviceConfig.hasTouchScreen = false;
    deviceConfig.hasPhysicalButtons = true;
    Serial.println("Device: M5StickC Plus");
  } 
  else if (board == m5::board_t::board_M5Stack || 
           board == m5::board_t::board_M5StackCore2) {
    deviceConfig.type = DEVICE_M5CORE2;
    deviceConfig.hasTouchScreen = true;
    deviceConfig.hasPhysicalButtons = false;
    Serial.println("Device: M5Core2");
  }
  else {
    // Fallback: detect by screen size
    if (deviceConfig.screenWidth == 320 && deviceConfig.screenHeight == 240) {
      deviceConfig.type = DEVICE_M5CORE2;
      deviceConfig.hasTouchScreen = true;
      deviceConfig.hasPhysicalButtons = false;
      Serial.println("Device: M5Core2 (detected by screen size)");
    } else {
      deviceConfig.type = DEVICE_M5STICK_CPLUS;
      deviceConfig.hasTouchScreen = false;
      deviceConfig.hasPhysicalButtons = true;
      Serial.println("Device: M5StickC Plus (fallback)");
    }
  }
  
}

/***************************************************************************************
** Function name: getDeviceType
** Description:   Return current device type
***************************************************************************************/
DeviceType getDeviceType() {
  return deviceConfig.type;
}

