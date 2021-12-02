/**************************************************************************/
/*!
    @file     Data.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v34 - First Public Release (Feature parity with ESP8266 Release v34)
*/
/**************************************************************************/

#ifndef _DATA_H_
#define _DATA_H_

#include <Arduino.h>
#include "input/Sensor.h"

class Sensor;

class Data {
  private:
    Sensor *_sensor;
    float _valueFloat;
    int _valueInt;
    boolean _valueBoolean;
    String _unit;
    int _type;
  public:
    Data(Sensor*, float, String);
    Data(Sensor*, int, String);
    Data(Sensor*, boolean, String);
    String getValueString(void);
    String getRequestString(void);
    Sensor* getSensor(void);
};

#endif