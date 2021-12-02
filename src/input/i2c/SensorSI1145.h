/**************************************************************************/
/*!
    @file     SensorSI1145.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v35 - Added Support for VEML6075 and SI1145 UVI Sensors
*/
/**************************************************************************/

#ifndef _SensorSI1145_h_
#define _SensorSI1145_h_

#include "input/Sensor.h"
// #include <Adafruit_SI1145.h>
#include <SI1145_WE.h>

class SensorSI1145 : public Sensor {
  private:
    // static Adafruit_SI1145 *si1145;
    static SI1145_WE *si1145;
    static boolean failedInit;
    static int lastCycleId;
    float lastPostedValue = NAN;
  protected:
    Data* read(bool);
    void preCycle(int);
    boolean smartSensorCheck(float, float, boolean);
    float calcLux(uint16_t vis, uint16_t ir);
  public:
    SensorSI1145 (long, String, String, String, String, String, int, int, float, SensorCalculation*);
};

#endif