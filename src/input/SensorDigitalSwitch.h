/**************************************************************************/
/*!
    @file     SensorDigitalSwitch.h
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

#ifndef _SensorDigitalSwitch_h_
#define _SensorDigitalSwitch_h_

#include "input/Sensor.h"

class SensorDigitalSwitch : public Sensor {
  private:
    bool lastPostedValue = 0;
    uint8_t _port;
  protected:
    Data* read(bool);
    void preCycle(int);
    boolean smartSensorCheck(float, float, boolean);
  public:
    SensorDigitalSwitch (long, String, String, String, uint8_t, int, int, SensorCalculation*);
};

#endif