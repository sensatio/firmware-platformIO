/**************************************************************************/
/*!
    @file     SensorMax44009.h
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

#include <MAX44009.h>
#include <Wire.h>

#ifndef _SensorMax44009_h_
#define _SensorMax44009_h_

#include "input/Sensor.h"

class SensorMax44009 : public Sensor {
  private:
    static MAX44009 *max44009;
    boolean failedInit;
    float lastPostedValue = NAN;
  protected:
    Data* read(bool);
    void preCycle(int);
    boolean smartSensorCheck(float, float, boolean);
  public:
    SensorMax44009 (long, String, String, String, String, String, int, int, float, SensorCalculation*);
};

#endif