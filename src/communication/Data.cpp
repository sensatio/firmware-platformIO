
/**************************************************************************/
/*!
    @file     Data.cpp
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

#include "Data.h"

Data::Data(Sensor *sensor, float value, String unit) {
  _type = 1;
  _valueFloat = value;
  _sensor = sensor;
  _unit = unit;
}

Data::Data(Sensor *sensor, int value, String unit) {
  _type = 2;
  _valueInt = value;
  _sensor = sensor;
  _unit = unit;
}

Data::Data(Sensor *sensor, boolean value, String unit) {
  _type = 3;
  _valueBoolean = value;
  _sensor = sensor;
  _unit = unit;
}

String Data::getRequestString() {

  String returnString = String(_sensor->getId()) +",";
  
  if(_type==1)
    returnString = returnString + String(_valueFloat);
  else if(_type==2)
    returnString = returnString + String(_valueInt);
  else if(_type==3)
  {
    if(_valueBoolean)
      returnString = returnString + "true";
    else
      returnString = returnString + "false";
      
  }
  
  return returnString+","+_unit;
  
}

String Data::getValueString() {

  if(_type==1)
    return String(_valueFloat);
  else if(_type==2)
    return String(_valueInt);
  else if(_type==3)
    return String(_valueBoolean);  

  return "";
}

Sensor* Data::getSensor() {
  return _sensor;
} 