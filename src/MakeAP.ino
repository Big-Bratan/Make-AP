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
  
  M5.Lcd.fillScreen(TFT_BLACK);
  // Display loading screen
  M5.Lcd.pushImage(0, 0, imgWidth, imgHeight, img);
  delay(2000);

  M5.Display.setTextColor(GREEN);
  M5.Display.setTextDatum(middle_center);
}

void loop() {
  M5.update(); // Update buttons state
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

      // If button B is pressed, go down the list
      if (M5.BtnB.wasPressed()) {
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
      
      // If the button A is pressed, confirm selection
      if (M5.BtnA.wasPressed()) {
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
            Serial.print("MAIN: RENDERING KEYBOARD");
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
    // Reboot on power button press if in AP view
    if (M5.BtnPWR.wasPressed()) {
      esp_restart();
    }
  }

  delay(100);
}
