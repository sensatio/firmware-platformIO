/**************************************************************************/
/*!
    @file     SensorAnalogue.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v32 - Added MQTT Support!
    v29 - First Public Release
*/
/**************************************************************************/

#ifndef _SensorAnalogue_h_
#define _SensorAnalogue_h_

#include "../Sensor.h"

class SensorAnalogue : public Sensor {
  private:
    int numberOfSamples;
    int _rSplit;
    float lastPostedValue = NAN;
    #ifdef ESP32_BOARD
      uint8_t _port;
    #endif
  protected:
    Data* read(bool);
    void preCycle(int);
    boolean smartSensorCheck(float, float, boolean);
  public:
    SensorAnalogue (long, String, String, String, uint8_t, int, int, float, SensorCalculation*);
    SensorAnalogue (long, String, String, String, int, uint8_t, int, int, float, SensorCalculation*);
};

#endif