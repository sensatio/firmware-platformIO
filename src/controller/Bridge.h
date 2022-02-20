/**************************************************************************/
/*!
    @file     Bridge.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v43 - Fixed data transmit issues in configurations with many sensors
    v42 - Fixed low memory issues in configurations with many sensors and a ST7735 Bug
    v41 - Renamed Display Class to support more types
    v40 - New Display Structure to enable Display Rotation, different Styles etc.
    v35 - Added Support for VEML6075 and SI1145 UVI Sensors
    v34 - First Public Release (Feature parity with ESP8266 Release v34)
*/
/**************************************************************************/

#ifndef _BRIDGE_H_
#define _BRIDGE_H_

#include <Esp.h>
#include <EEPROM.h>

#ifdef ESP8266_BOARD
  #include <WiFiClientSecureBearSSL.h>
#elif ESP32_BOARD
  #include <HTTPClient.h>
  #include <esp_int_wdt.h>
  #include <esp_task_wdt.h>
#endif

#include "StateHelper.h"
#include "UUID.h"
#include "OTA.h"
#include "communication/WiFiManager.h"
#include "communication/MQTT.h"
#include "input/Sensor.h"
#include "input/analog/SensorAnalogue.h"
#include "input/SensorDigitalSwitch.h"
#include "input/i2c/Ads1x15.h"
#include "input/i2c/SensorBMx280.h"
#include "input/i2c/SensorBME680.h"
#include "input/i2c/SensorMax44009.h"
#include "input/i2c/SensorBH1750.h"
#include "input/i2c/SensorVEML6075.h"
#include "input/i2c/SensorSI1145.h"
#include "input/onewire/SensorDHT.h"
#include "input/onewire/SensorDallas.h"
#include "output/display/Display.h"
#include "output/display/DisplayOLED128.h"
#include "output/display/DisplayST7735.h"
#include "output/VisualisationHelper.h"
#include "../input/i2c/SensorMCP9600.h"

#ifdef ESP8266_BOARD
  void initSSL();
#endif

void registerBridge();
void restoreBridgeConfig();
void restart();

void getBridgeConfig();
void configureBridge(JsonObject&);
void initVisualisationHelper(JsonObject&);
void configureDisplayValueData(int, JsonObject&);
void configureExpansionPort(int, JsonObject&);
void configurePort(int, JsonObject&);
void addSensor(Sensor *);
void loopSensor(int);
void loopDisplay(unsigned long);
boolean postSensorData(Data* data[], int);
boolean postSensorDataPart(Data* data[], int, int);
void checkStatus();
void trySleep(long);
void storeDisplayAndPowerConfig(boolean);
void doPowerSaving();
void doPowerSavingInit(boolean);
uint8_t translateGPIOPort(String);
void tryInitMQTT();
void handlePortConfigArray(JsonArray&);

#ifdef ESP32_BOARD
  uint8_t translateAnalogueGPIOPort(String);
#endif

#endif