/**************************************************************************/
/*!
    @file     RestServer.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v41 - Renamed Display Class to support more types
    v33 - Improved MQTT Setup Routine
    v32 - Added MQTT Support!
    v29 - First Public Release
*/
/**************************************************************************/

#ifndef _RESTSERVER_H_
#define _RESTSERVER_H_

#ifdef ESP8266_BOARD
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
#elif ESP32_BOARD
  #include <WiFi.h>
  #include <WebServer.h>
#endif

#include <ArduinoJson.h>

#include "controller/StateHelper.h"
#include "controller/UUID.h"
#include "output/display/Display.h"
#include "communication/WiFiManager.h"
#include "MQTT.h"

void startRestServer();
void loopRestserver();
void configRestServerRouting();
void androidCaptiveResponse();
void captiveResponse();
void tryIdentify();
void restGetUuid();
void handleNotFound();
bool captivePortal();
void handleRoot();
void returnNetworkList();
void presentWiFiSetupScreen();
void tryRestart();
void restUpdateName();
void handleAppleCaptivePortal();
void initMqtt();

String toStringIp(IPAddress ip);
bool isIp(String str);

#endif
