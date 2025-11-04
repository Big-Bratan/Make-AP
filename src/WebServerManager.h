#ifndef WEBSERVERMANAGER_H
#define WEBSERVERMANAGER_H

#include <Arduino.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <SD.h>
#include <vector>

// Web server and DNS server instances
extern WebServer* webServer;
extern DNSServer* dnsServer;

// Current serving state
extern bool isServingFile;
extern String currentServedFile;

/***************************************************************************************
** Function name: initSD
** Description:   Initialize SD card
***************************************************************************************/
bool initSD();

/***************************************************************************************
** Function name: getHTMLFiles
** Description:   Get list of HTML files from sites/ directory
***************************************************************************************/
std::vector<String> getHTMLFiles();

/***************************************************************************************
** Function name: startWebServer
** Description:   Start web server with selected HTML file
***************************************************************************************/
bool startWebServer(String filename);

/***************************************************************************************
** Function name: stopWebServer
** Description:   Stop web server and cleanup
***************************************************************************************/
void stopWebServer();

/***************************************************************************************
** Function name: handleWebServerClient
** Description:   Handle web server client requests (call in loop)
***************************************************************************************/
void handleWebServerClient();

/***************************************************************************************
** Function name: readFileContent
** Description:   Read file content from SD card with streaming support
***************************************************************************************/
String readFileContent(String filename);

/***************************************************************************************
** Function name: getContentType
** Description:   Get MIME type based on file extension
***************************************************************************************/
String getContentType(String filename);

#endif // WEBSERVERMANAGER_H

