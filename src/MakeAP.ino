#include <esp_system.h>
#include <WiFi.h>
#include "MyKeyboard.h"
#include "Constants.h"
#include "LoadingScreen.h"
#include "WebServerManager.h"

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

// File serving state (M5Core2 only)
bool browsingFiles = false;
bool waitingForServeButton = false;
std::vector<String> htmlFiles;
int fileSelectedIndex = 0;
int prevFileSelectedIndex = -1;


void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Serial.begin(9600);
  M5.Display.setRotation(1);
  
  // Initialize device detection
  initDeviceConfig();
  input.begin();
  
  // Initialize SD card for M5Core2
  if (deviceConfig.type == DEVICE_M5CORE2) {
    if (initSD()) {
      Serial.println("SD card ready");
    } else {
      Serial.println("SD card not available");
    }
  }
  
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

  // Handle web server if serving
  if (isServingFile) {
    handleWebServerClient();
  }

  // File browsing mode (M5Core2 only)
  if (browsingFiles) {
    // Render file list if changed (partial redraw - list area only)
    if (prevFileSelectedIndex != fileSelectedIndex) {
      displayFileList(htmlFiles, false);  // false = only redraw list items
      prevFileSelectedIndex = fileSelectedIndex;
    }

    // Navigation through files
    if (input.wasUpPressed() && htmlFiles.size() > 0) {
      fileSelectedIndex--;
      if (fileSelectedIndex < 0) {
        fileSelectedIndex = htmlFiles.size() - 1;
      }
    }
    
    if (input.wasDownPressed() && htmlFiles.size() > 0) {
      fileSelectedIndex++;
      if (fileSelectedIndex >= (int)htmlFiles.size()) {
        fileSelectedIndex = 0;
      }
    }
    
    // Select file and start serving
    if (input.wasSelectPressed() && htmlFiles.size() > 0) {
      String selectedFile = htmlFiles[fileSelectedIndex];
      
      if (startWebServer(selectedFile)) {
        browsingFiles = false;
        waitingForServeButton = true;  // Keep button active
        
        // Redraw AP screen with serving status
        drawAPWithServeButton();
        drawServingStatus(selectedFile);
      } else {
        // Show error and return to AP screen
        browsingFiles = false;
        drawAPWithServeButton();
      }
    }
    
    delay(100);
    return;
  }

  // Waiting for button press on AP screen (M5Core2 only)
  // Use InputHandler buttons: BtnA (left/UP) = RESTART, BtnC (right/DOWN) = SERVE
  if (waitingForServeButton && deviceConfig.type == DEVICE_M5CORE2) {
    // BtnA / UP button = RESTART
    if (input.wasUpPressed()) {
      esp_restart();
    }
    
    // BtnC / DOWN button = SERVE FILE
    if (input.wasDownPressed()) {
      // Stop current server if serving
      if (isServingFile) {
        stopWebServer();
      }
      
      // Get HTML files from SD card
      htmlFiles = getHTMLFiles();
      fileSelectedIndex = 0;
      prevFileSelectedIndex = -1;
      
      // Enter file browsing mode
      browsingFiles = true;
      displayFileList(htmlFiles, true);  // true = full redraw
      
      delay(100);
      return;
    }
  }

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
          // Display the AP view with serve button for M5Core2
          if (deviceConfig.type == DEVICE_M5CORE2) {
            drawAPWithServeButton();
            waitingForServeButton = true;
          } else {
            drawAP();
          }
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
          if (deviceConfig.type == DEVICE_M5CORE2) {
            drawAPWithServeButton();
            waitingForServeButton = true;
          } else {
            drawAP();
          }
        } else {
          selectedSSID = inputValue;
          inputValue = "";
          selectedIndex = 0;
          preSelectedIndex = selectedIndex;
        }
      }
    }
  } else {
    // AP is running - handle restart for M5StickC (M5Core2 uses touch buttons)
    if (deviceConfig.type != DEVICE_M5CORE2 && input.wasSelectPressed()) {
      esp_restart();
    }
  }

  delay(100);
}
