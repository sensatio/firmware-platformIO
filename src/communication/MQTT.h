/**************************************************************************/
/*!
    @file     MQTT.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v32 - Added MQTT Support!
*/
/**************************************************************************/

#ifndef _MQTT_h_
#define _MQTT_h_

#include <Arduino.h>
#include <PubSubClient.h>

#ifdef ESP8266_BOARD
  #include <ESP8266WiFi.h>
#elif ESP32_BOARD
  #include <WiFi.h>
#endif

#include "controller/UUID.h"
#include "Data.h"

class MQTT {
  private:
    unsigned long lastMillis;
    String _brokerUrl;
    long _brokerPort;
    String _username;
    String _password;
    WiFiClient espClient;
    PubSubClient* pubSubClient;
    String clientId;
    
  public:
    MQTT (char*, long);
    MQTT (char*, long, String, String);
    bool connect(void);
    void loop(void);
    void publishSensorData(Data* data[], int);
    void publishForAutoDiscovery(Sensor*);
};

#endif