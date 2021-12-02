/**************************************************************************/
/*!
    @file     SensorMax44009.cpp
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

#include "SensorMax44009.h"

extern boolean isResetting;
extern int powerMode;

MAX44009* SensorMax44009::max44009;

SensorMax44009::SensorMax44009 (long id, String category, String shortName, String name, String PortSDA, String PortSCL, int refreshInterval, int postDataInterval, float smartValueThreshold, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, smartValueThreshold, calculation, false) {

  int i=0;
  failedInit = false;

  while(max44009->begin())
  {
    Serial.println("Trying to find MAX44009 sensor!");
    delay(500);

    if(i==5)
    {
      Serial.println("Could not find a valid MAX44009 sensor, check wiring!");
      failedInit=true;
      break;
    }

    i++;
  }
}

void SensorMax44009::preCycle(int cycleId)
{
}

Data* SensorMax44009::read(bool shouldPostData)
{  
  if(!isResetting && !failedInit)
  {
    if(_calculation->getValueType()=="illuminance")
    {
      float illuminance = max44009->get_lux();
      shouldPostData = smartSensorCheck(illuminance, _smartValueThreshold, shouldPostData);
      return _calculation->calculate(this, illuminance, shouldPostData);
    }
  }
  return NULL;
}

boolean SensorMax44009::smartSensorCheck(float currentRawValue, float threshhold, boolean shouldPostData)
{
  if(powerMode == 3)
  {
    if(!shouldPostData)
    {
      if(!isnan(lastPostedValue))
      {
          if(lastPostedValue-currentRawValue>threshhold || lastPostedValue-currentRawValue<-threshhold)
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