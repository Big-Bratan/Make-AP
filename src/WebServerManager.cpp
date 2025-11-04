#include "WebServerManager.h"
#include <SPI.h>
#include <WiFi.h>

// M5Core2 SD card SPI pins
#define SD_SPI_CS_PIN   4
#define SD_SPI_SCK_PIN  18
#define SD_SPI_MISO_PIN 38
#define SD_SPI_MOSI_PIN 23

// DNS port for captive portal
#define DNS_PORT 53

// Global web server and DNS server instances
WebServer* webServer = nullptr;
DNSServer* dnsServer = nullptr;
bool isServingFile = false;
String currentServedFile = "";

/***************************************************************************************
** Function name: initSD
** Description:   Initialize SD card
***************************************************************************************/
bool initSD() {
  // Initialize SPI with M5Core2 specific pins
  SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);
  
  // Initialize SD card with CS pin, SPI instance, and frequency (25MHz)
  if (!SD.begin(SD_SPI_CS_PIN, SPI, 25000000)) {
    Serial.println("SD Card initialization failed");
    return false;
  }
  
  Serial.println("SD Card ready");
  return true;
}

/***************************************************************************************
** Function name: getHTMLFiles
** Description:   Get list of HTML files from sites/ directory
***************************************************************************************/
std::vector<String> getHTMLFiles() {
  std::vector<String> htmlFiles;
  
  // Check if sites directory exists
  if (!SD.exists("/sites")) {
    Serial.println("/sites directory not found");
    return htmlFiles;
  }
  
  // Open sites directory
  File sitesDir = SD.open("/sites");
  if (!sitesDir || !sitesDir.isDirectory()) {
    Serial.println("Failed to open /sites directory");
    return htmlFiles;
  }
  
  // List all HTML files
  File file = sitesDir.openNextFile();
  while (file) {
    String fileName = String(file.name());
    if (!file.isDirectory()) {
      String lowerName = fileName;
      lowerName.toLowerCase();
      if (lowerName.endsWith(".html") || lowerName.endsWith(".htm")) {
        htmlFiles.push_back(fileName);
      }
    }
    file = sitesDir.openNextFile();
  }
  
  sitesDir.close();
  Serial.println("Found " + String(htmlFiles.size()) + " HTML files");
  
  return htmlFiles;
}

/***************************************************************************************
** Function name: getContentType
** Description:   Get MIME type based on file extension
***************************************************************************************/
String getContentType(String filename) {
  if (filename.endsWith(".html") || filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".json")) return "application/json";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".jpg") || filename.endsWith(".jpeg")) return "image/jpeg";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".svg")) return "image/svg+xml";
  return "text/plain";
}

/***************************************************************************************
** Function name: readFileContent
** Description:   Read file content from SD card
***************************************************************************************/
String readFileContent(String filename) {
  String path = "/sites/" + filename;
  File file = SD.open(path);
  
  if (!file) {
    Serial.println("Failed to open: " + filename);
    return "";
  }
  
  String content = file.readString();
  file.close();
  
  return content;
}

/***************************************************************************************
** Function name: startWebServer
** Description:   Start web server with selected HTML file
***************************************************************************************/
bool startWebServer(String filename) {
  // Stop existing server if running
  if (webServer != nullptr) {
    stopWebServer();
  }
  
  // Read the HTML file content
  String htmlContent = readFileContent(filename);
  if (htmlContent.length() == 0) {
    return false;
  }
  
  // Create DNS server for captive portal (redirect all domains to AP IP)
  dnsServer = new DNSServer();
  IPAddress apIP = WiFi.softAPIP();
  
  // Start DNS server - redirect ALL domains to the AP IP
  if (!dnsServer->start(DNS_PORT, "*", apIP)) {
    Serial.println("DNS server failed to start!");
    delete dnsServer;
    dnsServer = nullptr;
  } else {
    Serial.println("All domains redirect to: " + apIP.toString());
  }
  
  // Create new web server instance
  webServer = new WebServer(80);
  
  // Serve the main HTML file
  webServer->on("/", [htmlContent]() {
    IPAddress clientIP = webServer->client().remoteIP();
    Serial.println("Client: " + clientIP.toString() + " -> GET /");
    webServer->send(200, "text/html", htmlContent);
  });
  
  // Handle other file requests from sites/ directory
  webServer->onNotFound([htmlContent]() {
    String path = webServer->uri();
    IPAddress clientIP = webServer->client().remoteIP();
    
    Serial.println("Client: " + clientIP.toString() + " -> GET " + path);
    
    // Remove leading slash for SD card path
    String pathNoSlash = path;
    if (pathNoSlash.startsWith("/")) {
      pathNoSlash = pathNoSlash.substring(1);
    }
    
    // Try to serve actual files from sites/ directory (CSS, JS, images, etc.)
    String fullPath = "/sites/" + pathNoSlash;
    if (SD.exists(fullPath)) {
      File file = SD.open(fullPath);
      if (file && !file.isDirectory()) {
        String contentType = getContentType(pathNoSlash);
        webServer->streamFile(file, contentType);
        file.close();
        Serial.println("  -> 200 OK (" + contentType + ")");
        return;
      }
    }

    webServer->send(200, "text/html", htmlContent);
  });
  
  // Start the server
  webServer->begin();
  
  isServingFile = true;
  currentServedFile = filename;
  
  Serial.println("Serving: " + filename);
  
  return true;
}

/***************************************************************************************
** Function name: stopWebServer
** Description:   Stop web server and cleanup
***************************************************************************************/
void stopWebServer() {
  if (dnsServer != nullptr) {
    dnsServer->stop();
    delete dnsServer;
    dnsServer = nullptr;
  }
  
  if (webServer != nullptr) {
    webServer->stop();
    delete webServer;
    webServer = nullptr;
  }
  
  isServingFile = false;
  currentServedFile = "";
}

/***************************************************************************************
** Function name: handleWebServerClient
** Description:   Handle web server client requests (call in loop)
***************************************************************************************/
void handleWebServerClient() {
  if (dnsServer != nullptr) {
    dnsServer->processNextRequest();
  }
  
  if (webServer != nullptr && isServingFile) {
    webServer->handleClient();
  }
}

