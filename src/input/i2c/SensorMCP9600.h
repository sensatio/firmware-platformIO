/**************************************************************************/
/*!
    @file     SensorMCP9600.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v47 - Added Support for MCP9600 thermocouple sensors
*/
/**************************************************************************/

#include <SparkFun_MCP9600.h>

#ifndef _SensorMCP9600_h_
#define _SensorMCP9600_h_

#include "../Sensor.h"

class SensorMCP9600 : public Sensor {
  private:
    static MCP9600 *mcp9600_60;
    static MCP9600 *mcp9600_66;
    static MCP9600 *mcp9600_67;
    MCP9600* mcp;
    boolean failedInit;
    float lastPostedValue = NAN;
  protected:
    Data* read(bool);
    void preCycle(int);
    boolean smartSensorCheck(float, float, boolean);
  public:
    SensorMCP9600 (long, String, String, String, String, String, int, int, float, SensorCalculation*);
};



#endif /* _SensorMCP9600_h_ */
