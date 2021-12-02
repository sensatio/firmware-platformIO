/**************************************************************************/
/*!
    @file     OTA.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v39 - Changed automatic Update to only if required Update
    v34 - First Public Release (Feature parity with ESP8266 Release v34)
*/
/**************************************************************************/

#ifndef _OTA_H_
#define _OTA_H_

#ifdef ESP8266_BOARD
  #include <ESP8266httpUpdate.h>
#elif ESP32_BOARD
  #include <ArduinoOTA.h>
  #include <WiFiClient.h>
  #include <HTTPUpdate.h>
#endif

#include "StateHelper.h"
#include "../output/display/DisplayOLED128.h"
#include "Bridge.h"

void tryFirmwareUpdate(String fwUpdateToken);

#endif