/**************************************************************************/
/*!
    @file     SensorBH1750.cpp
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

#include "SensorBH1750.h"

extern boolean isResetting;
extern int powerMode;

BH1750* SensorBH1750::bh1750;

SensorBH1750::SensorBH1750 (long id, String category, String shortName, String name, String PortSDA, String PortSCL, int refreshInterval, int postDataInterval, float smartValueThreshold, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, smartValueThreshold, calculation, false) {

  if(bh1750==NULL)
  {
    bh1750 = new BH1750();

    bh1750->begin();
  }
}

void SensorBH1750::preCycle(int cycleId)
{
}

Data* SensorBH1750::read(bool shouldPostData)
{  
  if(!isResetting)
  {
    if(_calculation->getValueType()=="illuminance")
    {
      float illuminance = bh1750->readLightLevel();

      if(illuminance>=0)
      {
        shouldPostData = smartSensorCheck(illuminance, _smartValueThreshold, shouldPostData);
        return _calculation->calculate(this, illuminance, shouldPostData);
      }
      else
        Serial.println("NAN Illuminance!");
    }
  }
 
  return NULL;
}

boolean SensorBH1750::smartSensorCheck(float currentRawValue, float threshhold, boolean shouldPostData)
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