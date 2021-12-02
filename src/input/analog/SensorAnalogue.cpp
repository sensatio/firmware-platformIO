/**************************************************************************/
/*!
    @file     SensorAnalogue.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v34 - Added Generic Analog Sensor Support
    v33 - Changes for Digital Sensor Switch Support
    v29 - First Public Release
    v32 - Added MQTT Support!
*/
/**************************************************************************/

#include "SensorAnalogue.h"

extern boolean isResetting;
extern int powerMode;

SensorAnalogue::SensorAnalogue (long id, String category, String shortName, String name, uint8_t port, int refreshInterval, int postDataInterval, float smartValueThreshold, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, smartValueThreshold, calculation, false) {

  #ifdef ESP32_BOARD
    pinMode(port, INPUT);
    _port = port;
  #endif

}

SensorAnalogue::SensorAnalogue (long id, String category, String shortName, String name, int rSplit, uint8_t port, int refreshInterval, int postDataInterval, float smartValueThreshold, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, smartValueThreshold, calculation, false) {

  #ifdef ESP32_BOARD
    pinMode(port, INPUT);
    _port = port;
  #endif

  _rSplit = rSplit;
 
}

void SensorAnalogue::preCycle(int cycleId)
{
}

Data* SensorAnalogue::read(bool shouldPostData)
{
  if(!isResetting)
  {
    float adc = 0;

    for (int i = 0; i < 10; i++)
    {
      #ifdef ESP8266_BOARD
        adc = adc + (float) analogRead(0); // ADC = A0
      #elif ESP32_BOARD
        adc = adc + (float) analogRead(_port);
      #endif
    }

    adc = adc / 10.0;
    
    if(!std::isinf(adc))
    {
      if(_rSplit!=0)
      {
        double rT = ((double) adc)*_rSplit/(1023-adc);
        shouldPostData = smartSensorCheck(rT, _smartValueThreshold, shouldPostData);
        return _calculation->calculate(this, (float)rT, shouldPostData);
      }
      else
      {
        shouldPostData = smartSensorCheck(adc, _smartValueThreshold, shouldPostData);
        return _calculation->calculate(this, adc, shouldPostData);
      }
    }
  }

  return NULL;

}

boolean SensorAnalogue::smartSensorCheck(float currentRawValue, float threshhold, boolean shouldPostData)
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