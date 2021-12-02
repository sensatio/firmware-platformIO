/**************************************************************************/
/*!
    @file     WiFiManager.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v29 - First Public Release
*/
/**************************************************************************/

#ifndef _WIFIMANAGER_H_
#define _WIFIMANAGER_H_

#include <EEPROM.h>
#include <DNSServer.h>
#include <ArduinoJson.h>

#ifdef ESP8266_BOARD
  #include <ESP8266WiFi.h>
  #include <ESP8266httpUpdate.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266mDNS.h>
  #include "Hash.h"
#elif ESP32_BOARD
  #include <WiFi.h>
  #include <ArduinoOTA.h>
  #include <ESPmDNS.h>
  #include <WebServer.h>
#endif

#include "output/display/Display.h"
#include "controller/StateHelper.h"
#include "controller/Bridge.h"

void connectToNetwork();
void connectToAP();
bool startUpLocalAP();
void setupBridgeConfig();
void resetBridgeConfig();
void setupBridgeConfigManual();
void shutDownWiFi();
void startDNS();
void loopDNS();
void checkWiFiStatus();

#endif