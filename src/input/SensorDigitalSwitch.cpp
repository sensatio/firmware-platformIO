/**************************************************************************/
/*!
    @file     SensorDigitalSwitch.cpp
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

#include "SensorDigitalSwitch.h"

extern boolean isResetting;
extern int powerMode;

SensorDigitalSwitch::SensorDigitalSwitch (long id, String category, String shortName, String name, uint8_t port, int refreshInterval, int postDataInterval, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, 0.5, calculation, true) {

    pinMode(port, INPUT);
    _port = port;

}

void SensorDigitalSwitch::preCycle(int cycleId)
{
}

Data* SensorDigitalSwitch::read(bool shouldPostData)
{
  if(!isResetting)
  {
    bool portState = digitalRead(_port);  
    if(lastPostedValue!=portState)
        shouldPostData = true;
    
    Data *data = _calculation->calculate(this, portState, shouldPostData);
    
    if(shouldPostData)
        lastPostedValue = portState;
    
    return data;
  }

  return NULL;

}

boolean SensorDigitalSwitch::smartSensorCheck(float currentRawValue, float threshhold, boolean shouldPostData)
{
  if(powerMode == 3)
  {
    if(!shouldPostData)
    {
      if(!isnan(lastPostedValue))
      {
          if(lastPostedValue-currentRawValue>threshhold|| lastPostedValue-currentRawValue<-threshhold)
          {
            shouldPostData = true;
          }
      }
    }

    if(shouldPostData)
      lastPostedValue = currentRawValue;
  }

  return shouldPostData;
}