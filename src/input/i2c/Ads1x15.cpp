/**************************************************************************/
/*!
    @file     Ads1x15.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v47 - Fixed a bug that caused a crash if multiple ADS1115 were configured
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v34 - First Public Release (Feature parity with ESP8266 Release v34)
*/
/**************************************************************************/

#include "Ads1x15.h"

boolean Ads1x15::init48 = false;
boolean Ads1x15::init49 = false;
boolean Ads1x15::init4A = false;
boolean Ads1x15::init4B = false;
Adafruit_ADS1015* Ads1x15::ads1x15_48 = NULL;
Adafruit_ADS1015* Ads1x15::ads1x15_49 = NULL;
Adafruit_ADS1015* Ads1x15::ads1x15_4A = NULL;
Adafruit_ADS1015* Ads1x15::ads1x15_4B = NULL;

extern int powerMode;

Ads1x15::Ads1x15 (long id, String category, String shortName, String name, String type, String addressString, int channel, int preResistor, int postResistor, int refreshInterval, int postDataInterval, float smartValueThreshold, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, smartValueThreshold, calculation, false) {

  _channel = channel;
  numberOfSamples = 10;
  _preResistor = (float) preResistor;
  _postResistor = (float) postResistor;

if ((addressString == NULL) || (addressString == "") || (addressString == "0x48")) {
    if (!init48)
    {
      Serial.println("I48");
      init48 = true;

      if(type == "ADS1115")
        ads1x15_48 = new Adafruit_ADS1115(0x48);
      else
        ads1x15_48 = new Adafruit_ADS1015(0x48);

      ads1x15_48->setGain(GAIN_TWOTHIRDS);
      ads1x15_48->begin();
    }
    ads1x15 = ads1x15_48;
  }
  else if (addressString == "0x49") {
    if (!init49)
    {
      Serial.println("I49");
      init49 = true;

      if(type == "ADS1115")
        ads1x15_49 = new Adafruit_ADS1115(0x49);
      else
        ads1x15_49 = new Adafruit_ADS1015(0x49);

      ads1x15_49->setGain(GAIN_TWOTHIRDS);
      ads1x15_49->begin();
    }
    ads1x15 = ads1x15_49;
  }

  else if (addressString == "0x4A") {
    if (!init4A)
    {
      Serial.println("I4A");
      init4A = true;

      if(type == "ADS1115")
        ads1x15_4A = new Adafruit_ADS1115(0x4A);
      else
        ads1x15_4A = new Adafruit_ADS1015(0x4A);

      ads1x15_4A->setGain(GAIN_TWOTHIRDS);
      ads1x15_4A->begin();
    }
    ads1x15 = ads1x15_4A;
  }
  else if (addressString == "0x4B") {
    if (!init4B)
    {
      Serial.println("I4B");
      init4B = true;

      if(type == "ADS1115")
        ads1x15_4B = new Adafruit_ADS1115(0x4B);
      else
        ads1x15_4B = new Adafruit_ADS1015(0x4B);

      ads1x15_4B->setGain(GAIN_TWOTHIRDS);
      ads1x15_4B->begin();
    }
    ads1x15 = ads1x15_4B;
  }

}

void Ads1x15::preCycle(int cycleId)
{
}

Data* Ads1x15::read(bool shouldPostData)
{
  float adcMax = 0;
  float adc = 0;

  for (int i = 0; i < numberOfSamples; i++)
  {
    adcMax = adcMax + (float) ads1x15->readADC_SingleEnded(0);

    if (_channel == 1)
      adc = adc + (float) ads1x15->readADC_SingleEnded(1);
    if (_channel == 2)
      adc = adc + (float) ads1x15->readADC_SingleEnded(2);
    if (_channel == 3)
      adc = adc + (float) ads1x15->readADC_SingleEnded(3);
  }

  adcMax = adcMax / (float)numberOfSamples;
  adc = adc / (float)numberOfSamples;

  if (adc >= adcMax-20)
    adc = adcMax;

  if((_preResistor!=0 && _postResistor!=0) || (_preResistor==0 && _postResistor==0))
  {
    shouldPostData = smartSensorCheck(adc, _smartValueThreshold, shouldPostData);
    return _calculation->calculate(this, adc, shouldPostData);
  }
  else
  {
    float res = NULL;

    if(_preResistor>0)
      res = _preResistor / (adcMax / adc - 1.0);
    else if(_postResistor>0)
      res = _postResistor * (adcMax / adc - 1.0);

    if(res!=NULL && !std::isinf(res))
    {
      // Serial.printf("Corrected res: %f\n\r",res);
      shouldPostData = smartSensorCheck(res, _smartValueThreshold, shouldPostData);
      return _calculation->calculate(this, res, shouldPostData);
    }
  }

  return NULL;

}

boolean Ads1x15::smartSensorCheck(float currentRawValue, float threshhold, boolean shouldPostData)
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
