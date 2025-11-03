#include <esp_system.h>
#include <WiFi.h>
#include "MyKeyboard.h"
#include "Constants.h"
#include "LoadingScreen.h"

// Default SSIDs list
const char* ssidList[] = {"Open keyboard", "FreeWifi", "Freebox-78K09B", "Test-AP"};
const int ssidCount = sizeof(ssidList) / sizeof(ssidList[0]);

// Default passwords list
const char* passwordList[] = {"Open keyboard", "admin123", "S3cR3T_P@sSwRd", "B!gBr@taN"};
const int passwordCount = sizeof(passwordList) / sizeof(passwordList[0]);

int prevSelectedIndex;
int selectedIndex = 0; // Current SSID or Password index

String selectedSSID;
String selectedPassword;
String inputValue; // Value of the keyboard text field
bool isKeyboardOpen = false;
bool renderList = true;
bool creatingAP = false;


void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Serial.begin(9600);
  M5.Display.setRotation(1);
  
  // Initialize device detection
  initDeviceConfig();
  input.begin();
  
  M5.Lcd.fillScreen(TFT_BLACK);
  // Display loading screen (centered for M5Core2: 320x240 screen, image is 240x135)
  int loadingX = (deviceConfig.type == DEVICE_M5CORE2) ? (WIDTH - imgWidth) / 2 : 0;
  int loadingY = (deviceConfig.type == DEVICE_M5CORE2) ? (HEIGHT - imgHeight) / 2 : 0;
  M5.Lcd.pushImage(loadingX, loadingY, imgWidth, imgHeight, img);
  delay(2000);

  M5.Display.setTextColor(GREEN);
  M5.Display.setTextDatum(middle_center);
  
  Serial.println("Setup complete!");
}

void loop() {
  M5.update(); // Update buttons state
  input.update(); // Update input handler
  static int preSelectedIndex = -1; // Track previous selection

  if (!creatingAP) {
    if (!isKeyboardOpen) {
      if (prevSelectedIndex != selectedIndex || renderList) {
        if (selectedSSID == "") {
          // Display the SSIDs list if none is selected
          displayList("AP SSID", ssidList, ssidCount);
        } else if (selectedPassword == "") {
          // Display the passwords list if an SSID is selected but no password is
          displayList("AP password", passwordList, passwordCount);
        } else {
          // Display the AP view
          drawAP();
        }
        prevSelectedIndex = selectedIndex;
        // Avoid too many render
        renderList = false;
      }

      // Handle list navigation - Device agnostic using InputHandler
      // UP button (M5Core2 left / M5Stick PWR)
      if (input.wasUpPressed()) {
        selectedIndex--;
        if (selectedIndex < 0) {
          // Wrap to bottom
          if (selectedSSID != "") {
            selectedIndex = passwordCount - 1;
          } else {
            selectedIndex = ssidCount - 1;
          }
        }
      }
      
      // DOWN button (M5Core2 right / M5Stick BtnB)
      if (input.wasDownPressed()) {
        selectedIndex++;
        if (selectedSSID != "") {
          if (selectedIndex >= passwordCount) {
            selectedIndex = 0;
          }
        } else {
          if (selectedIndex >= ssidCount) {
            selectedIndex = 0;
          }
        }
      }
      
      // SELECT button (M5Core2 center / M5Stick BtnA)
      if (input.wasSelectPressed()) {
        if (selectedSSID != "") {
          // Set selected password
          if (selectedIndex == 0) {
            isKeyboardOpen = true;
            hasMinLenToValidate = true;
            drawKeyboard(selectedPassword, false, 0, 0, -1, -1);
          } else {
            selectedPassword = passwordList[selectedIndex];
            inputValue = passwordList[selectedIndex];
            selectedIndex = 0;
          }
        } else {
          // Set selected SSID
          if (selectedIndex == 0) {
            isKeyboardOpen = true;
            drawKeyboard(selectedSSID, false, 0, 0, -1, -1);
          } else {
            selectedSSID = ssidList[selectedIndex];
            selectedIndex = 0;
          }
        }
      }
    } else {
      handleKeyboardInput();
      // Check if keyboard is closed and SSID is selected
      if (!isKeyboardOpen && inputValue != "") {
        if (selectedSSID != "") {
          selectedPassword = inputValue;
          selectedIndex = 0;
          drawAP();
        } else {
          selectedSSID = inputValue;
          inputValue = "";
          selectedIndex = 0;
          preSelectedIndex = selectedIndex;
        }
      }
    }
  } else {
    // Reboot on select button press for both devices
    if (input.wasSelectPressed()) {
      esp_restart();
    }
  }

  delay(100);
}
