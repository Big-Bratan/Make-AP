#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include <M5Unified.h>

// Detect which device we're running on
enum DeviceType {
  DEVICE_UNKNOWN,
  DEVICE_M5STICK_CPLUS,
  DEVICE_M5CORE2
};

// Device-specific configuration
struct DeviceConfig {
  int screenWidth;
  int screenHeight;
  bool hasTouchScreen;
  bool hasPhysicalButtons;
  DeviceType type;
};

// Global device configuration
extern DeviceConfig deviceConfig;

// Initialize device detection
void initDeviceConfig();

// Get current device type
DeviceType getDeviceType();

#endif // DEVICECONFIG_H

