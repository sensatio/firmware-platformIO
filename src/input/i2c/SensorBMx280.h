/**************************************************************************/
/*!
    @file     SensorBMx280.h
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

#include <BME280I2C.h>
// #include <Wire.h>

#ifndef _SensorBMx280_h_
#define _SensorBMx280_h_

#include "input/Sensor.h"

class SensorBMx280 : public Sensor {
  private:
    static BME280I2C* bme76;
    static BME280I2C* bme77;
    BME280I2C* bme;
    float lastPostedValue = NAN;
  protected:
    Data* read(bool);
    void preCycle(int);
    boolean smartSensorCheck(float, float, boolean);
  public:
    SensorBMx280 (long, String, String, String, String, int, int, float, SensorCalculation*);
};

#endif