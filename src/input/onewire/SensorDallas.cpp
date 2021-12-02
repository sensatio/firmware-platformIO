/**************************************************************************/
/*
    @file     SensorDallas.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v33 - Changes for Digital Sensor Switch Support
    v32 - Added MQTT Support!
    v29 - First Public Release
*/
/**************************************************************************/

#include "SensorDallas.h"

boolean SensorDallas::initDallas0 = false;
boolean SensorDallas::initDallas1 = false;
boolean SensorDallas::initDallas2 = false;
boolean SensorDallas::initDallas3 = false;
boolean SensorDallas::initDallas4 = false;
boolean SensorDallas::initDallas5 = false;
boolean SensorDallas::initDallas6 = false;
boolean SensorDallas::initDallas7 = false;
boolean SensorDallas::initDallas8 = false;
boolean SensorDallas::initDallas9 = false;
boolean SensorDallas::initDallas10 = false;
boolean SensorDallas::initDallas11 = false;
boolean SensorDallas::initDallas12 = false;
boolean SensorDallas::initDallas13 = false;
boolean SensorDallas::initDallas14 = false;
boolean SensorDallas::initDallas15 = false;
boolean SensorDallas::initDallas16 = false;
boolean SensorDallas::initDallas17 = false;
boolean SensorDallas::initDallas18 = false;
boolean SensorDallas::initDallas19 = false;
boolean SensorDallas::initDallas21 = false;
boolean SensorDallas::initDallas22 = false;
boolean SensorDallas::initDallas23 = false;
boolean SensorDallas::initDallas25 = false;
boolean SensorDallas::initDallas26 = false;
boolean SensorDallas::initDallas27 = false;
boolean SensorDallas::initDallas32 = false;
boolean SensorDallas::initDallas33 = false;
OneWire* SensorDallas::oneWire0  = NULL;
OneWire* SensorDallas::oneWire1  = NULL;
OneWire* SensorDallas::oneWire2  = NULL;
OneWire* SensorDallas::oneWire3  = NULL;
OneWire* SensorDallas::oneWire4  = NULL;
OneWire* SensorDallas::oneWire5  = NULL;
OneWire* SensorDallas::oneWire6  = NULL;
OneWire* SensorDallas::oneWire7  = NULL;
OneWire* SensorDallas::oneWire8  = NULL;
OneWire* SensorDallas::oneWire9  = NULL;
OneWire* SensorDallas::oneWire10  = NULL;
OneWire* SensorDallas::oneWire11  = NULL;
OneWire* SensorDallas::oneWire12  = NULL;
OneWire* SensorDallas::oneWire13  = NULL;
OneWire* SensorDallas::oneWire14  = NULL;
OneWire* SensorDallas::oneWire15  = NULL;
OneWire* SensorDallas::oneWire16  = NULL;
OneWire* SensorDallas::oneWire17 = NULL;
OneWire* SensorDallas::oneWire18 = NULL;
OneWire* SensorDallas::oneWire19 = NULL;
OneWire* SensorDallas::oneWire21 = NULL;
OneWire* SensorDallas::oneWire22 = NULL;
OneWire* SensorDallas::oneWire23 = NULL;
OneWire* SensorDallas::oneWire25 = NULL;
OneWire* SensorDallas::oneWire26 = NULL;
OneWire* SensorDallas::oneWire27 = NULL;
OneWire* SensorDallas::oneWire32 = NULL;
OneWire* SensorDallas::oneWire33 = NULL;
DallasTemperature* SensorDallas::dallasTemperature0 = NULL;
DallasTemperature* SensorDallas::dallasTemperature1 = NULL;
DallasTemperature* SensorDallas::dallasTemperature2 = NULL;
DallasTemperature* SensorDallas::dallasTemperature3 = NULL;
DallasTemperature* SensorDallas::dallasTemperature4 = NULL;
DallasTemperature* SensorDallas::dallasTemperature5 = NULL;
DallasTemperature* SensorDallas::dallasTemperature6 = NULL;
DallasTemperature* SensorDallas::dallasTemperature7 = NULL;
DallasTemperature* SensorDallas::dallasTemperature8 = NULL;
DallasTemperature* SensorDallas::dallasTemperature9 = NULL;
DallasTemperature* SensorDallas::dallasTemperature10 = NULL;
DallasTemperature* SensorDallas::dallasTemperature11 = NULL;
DallasTemperature* SensorDallas::dallasTemperature12 = NULL;
DallasTemperature* SensorDallas::dallasTemperature13 = NULL;
DallasTemperature* SensorDallas::dallasTemperature14 = NULL;
DallasTemperature* SensorDallas::dallasTemperature15 = NULL;
DallasTemperature* SensorDallas::dallasTemperature16 = NULL;
DallasTemperature* SensorDallas::dallasTemperature17 = NULL;
DallasTemperature* SensorDallas::dallasTemperature18 = NULL;
DallasTemperature* SensorDallas::dallasTemperature19 = NULL;
DallasTemperature* SensorDallas::dallasTemperature21 = NULL;
DallasTemperature* SensorDallas::dallasTemperature22 = NULL;
DallasTemperature* SensorDallas::dallasTemperature23 = NULL;
DallasTemperature* SensorDallas::dallasTemperature25 = NULL;
DallasTemperature* SensorDallas::dallasTemperature26 = NULL;
DallasTemperature* SensorDallas::dallasTemperature27 = NULL;
DallasTemperature* SensorDallas::dallasTemperature32 = NULL;
DallasTemperature* SensorDallas::dallasTemperature33 = NULL;

extern boolean isResetting;
extern int powerMode;

SensorDallas::SensorDallas (long id, String category, String shortName, String name, uint8_t port, int channel, int refreshInterval, int postDataInterval, float smartValueThreshold, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, smartValueThreshold, calculation, false) {

  _channel = channel;

  if(port==0)
  {
    if(!initDallas0)
    {
      initDallas0=true;
      oneWire0 = new OneWire(0);
      dallasTemperature0 = new DallasTemperature(oneWire0);
      dallasTemperature0->begin();
    }
    dallasTemperature = dallasTemperature0;
  }
  else if(port==1)
  {
    if(!initDallas1)
    {
      initDallas1=true;
      oneWire1 = new OneWire(1);
      dallasTemperature1 = new DallasTemperature(oneWire1);
      dallasTemperature1->begin();
    }
    dallasTemperature = dallasTemperature1;
  }
  else if(port==2)
  {
    if(!initDallas2)
    {
      initDallas2=true;
      oneWire2 = new OneWire(2);
      dallasTemperature2 = new DallasTemperature(oneWire2);
      dallasTemperature2->begin();
    }
    dallasTemperature = dallasTemperature2;
  }
  else if(port==3)
  {
    if(!initDallas3)
    {
      initDallas3=true;
      oneWire3 = new OneWire(3);
      dallasTemperature3 = new DallasTemperature(oneWire3);
      dallasTemperature3->begin();
    }
    dallasTemperature = dallasTemperature3;
  }
  else if(port==4)
  {
    if(!initDallas4)
    {
      initDallas4=true;
      oneWire4 = new OneWire(4);
      dallasTemperature4 = new DallasTemperature(oneWire4);
      dallasTemperature4->begin();
    }
    dallasTemperature = dallasTemperature4;
  }
  else if(port==5)
  {
    if(!initDallas5)
    {
      initDallas5=true;
      oneWire5 = new OneWire(5);
      dallasTemperature5 = new DallasTemperature(oneWire5);
      dallasTemperature5->begin();
    }
    dallasTemperature = dallasTemperature5;
  }
  else if(port==6)
  {
    if(!initDallas6)
    {
      initDallas6=true;
      oneWire6 = new OneWire(6);
      dallasTemperature6 = new DallasTemperature(oneWire6);
      dallasTemperature6->begin();
    }
    dallasTemperature = dallasTemperature6;
  }
  else if(port==7)
  {
    if(!initDallas7)
    {
      initDallas7=true;
      oneWire7 = new OneWire(7);
      dallasTemperature7 = new DallasTemperature(oneWire7);
      dallasTemperature7->begin();
    }
    dallasTemperature = dallasTemperature7;
  }
  else if(port==8)
  {
    if(!initDallas8)
    {
      initDallas8=true;
      oneWire8 = new OneWire(8);
      dallasTemperature8 = new DallasTemperature(oneWire8);
      dallasTemperature8->begin();
    }
    dallasTemperature = dallasTemperature8;
  }
  else if(port==9)
  {
    if(!initDallas9)
    {
      initDallas9=true;
      oneWire9 = new OneWire(9);
      dallasTemperature9 = new DallasTemperature(oneWire9);
      dallasTemperature9->begin();
    }
    dallasTemperature = dallasTemperature9;
  }
  else if(port==10)
  {
    if(!initDallas10)
    {
      initDallas10=true;
      oneWire10 = new OneWire(10);
      dallasTemperature10 = new DallasTemperature(oneWire10);
      dallasTemperature10->begin();
    }
    dallasTemperature = dallasTemperature10;
  }
  else if(port==11)
  {
    if(!initDallas11)
    {
      initDallas11=true;
      oneWire11 = new OneWire(11);
      dallasTemperature11 = new DallasTemperature(oneWire11);
      dallasTemperature11->begin();
    }
    dallasTemperature = dallasTemperature11;
  }
  else if(port==12)
  {
    if(!initDallas12)
    {
      initDallas12=true;
      oneWire12 = new OneWire(12);
      dallasTemperature12 = new DallasTemperature(oneWire12);
      dallasTemperature12->begin();
    }
    dallasTemperature = dallasTemperature12;
  }
  else if(port==13)
  {
    if(!initDallas13)
    {
      initDallas13=true;
      oneWire13 = new OneWire(13);
      dallasTemperature13 = new DallasTemperature(oneWire13);
      dallasTemperature13->begin();
    }
    dallasTemperature = dallasTemperature13;
  }
  else if(port==14)
  {
    if(!initDallas14)
    {
      initDallas14=true;
      oneWire14 = new OneWire(14);
      dallasTemperature14 = new DallasTemperature(oneWire14);
      dallasTemperature14->begin();
    }
    dallasTemperature = dallasTemperature14;
  }
  else if(port==15)
  {
    if(!initDallas15)
    {
      initDallas15=true;
      oneWire15 = new OneWire(15);
      dallasTemperature15 = new DallasTemperature(oneWire15);
      dallasTemperature15->begin();
    }
    dallasTemperature = dallasTemperature15;
  }
  else if(port==16)
  {
    if(!initDallas16)
    {
      initDallas16=true;
      oneWire16 = new OneWire(16);
      dallasTemperature16 = new DallasTemperature(oneWire16);
      dallasTemperature16->begin();
    }
    dallasTemperature = dallasTemperature16;
  }
  else if(port==17)
  {
    if(!initDallas17)
    {
      initDallas17=true;
      oneWire17 = new OneWire(17);
      dallasTemperature17 = new DallasTemperature(oneWire17);
      dallasTemperature17->begin();
    }
    dallasTemperature = dallasTemperature17;
  }
  else if(port==18)
  {
    if(!initDallas18)
    {
      initDallas18=true;
      oneWire18 = new OneWire(18);
      dallasTemperature18 = new DallasTemperature(oneWire18);
      dallasTemperature18->begin();
    }
    dallasTemperature = dallasTemperature18;
  }
  else if(port==19)
  {
    if(!initDallas19)
    {
      initDallas19=true;
      oneWire19 = new OneWire(19);
      dallasTemperature19 = new DallasTemperature(oneWire19);
      dallasTemperature19->begin();
    }
    dallasTemperature = dallasTemperature19;
  }
  else if(port==21)
  {
    if(!initDallas21)
    {
      initDallas21=true;
      oneWire21 = new OneWire(21);
      dallasTemperature21 = new DallasTemperature(oneWire21);
      dallasTemperature21->begin();
    }
    dallasTemperature = dallasTemperature21;
  }
  else if(port==22)
  {
    if(!initDallas22)
    {
      initDallas22=true;
      oneWire22 = new OneWire(22);
      dallasTemperature22 = new DallasTemperature(oneWire22);
      dallasTemperature22->begin();
    }
    dallasTemperature = dallasTemperature22;
  }
  else if(port==23)
  {
    if(!initDallas23)
    {
      initDallas23=true;
      oneWire23 = new OneWire(23);
      dallasTemperature23 = new DallasTemperature(oneWire23);
      dallasTemperature23->begin();
    }
    dallasTemperature = dallasTemperature23;
  }
  else if(port==25)
  {
    if(!initDallas25)
    {
      initDallas25=true;
      oneWire25 = new OneWire(25);
      dallasTemperature25 = new DallasTemperature(oneWire25);
      dallasTemperature25->begin();
    }
    dallasTemperature = dallasTemperature25;
  }
  else if(port==26)
  {
    if(!initDallas26)
    {
      initDallas26=true;
      oneWire26 = new OneWire(26);
      dallasTemperature26 = new DallasTemperature(oneWire26);
      dallasTemperature26->begin();
    }
    dallasTemperature = dallasTemperature26;
  }
  else if(port==27)
  {
    if(!initDallas27)
    {
      initDallas27=true;
      oneWire27 = new OneWire(27);
      dallasTemperature27 = new DallasTemperature(oneWire27);
      dallasTemperature27->begin();
    }
    dallasTemperature = dallasTemperature27;
  }
  else if(port==32)
  {
    if(!initDallas32)
    {
      initDallas32=true;
      oneWire32 = new OneWire(32);
      dallasTemperature32 = new DallasTemperature(oneWire32);
      dallasTemperature32->begin();
    }
    dallasTemperature = dallasTemperature32;
  }
  else if(port==33)
  {
    if(!initDallas33)
    {
      initDallas33=true;
      oneWire33 = new OneWire(33);
      dallasTemperature33 = new DallasTemperature(oneWire33);
      dallasTemperature33->begin();
    }
    dallasTemperature = dallasTemperature33;
  }
  
  numberOfDevices = dallasTemperature->getDeviceCount();

  if(_channel<numberOfDevices)
    dallasTemperature->getAddress(_address, channel);

}

void SensorDallas::preCycle(int cycleId)
{
}

Data* SensorDallas::read(bool shouldPostData)
{  
  if(!isResetting && numberOfDevices>0 && _channel<numberOfDevices)
  {    
    dallasTemperature->requestTemperaturesByAddress(_address);
    float tempC = dallasTemperature->getTempC(_address);

    if(tempC==-127.00 || tempC==85.00)
    {
      for(int i=0;i<10;i++)
      {
        dallasTemperature->requestTemperaturesByAddress(_address);
        delay(50);
        yield();
        tempC = dallasTemperature->getTempC(_address);
        delay(100);
        yield();

        if(tempC!=-127.00 && tempC!=85.00)
          break;
      }
    }
    
    if(tempC!=-127.00 && tempC!=85.00) {
      shouldPostData = smartSensorCheck(tempC, 0.3f, shouldPostData);
      return _calculation->calculate(this, tempC, shouldPostData);
    }
  }

  return NULL;

}

boolean SensorDallas::smartSensorCheck(float currentRawValue, float threshhold, boolean shouldPostData)
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