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

#include "SensorMCP9600.h"
#include "Wire.h"
#include "Adafruit_MCP9600.h"

extern boolean isResetting;
extern int powerMode;

MCP9600* SensorMCP9600::mcp9600_60;
MCP9600* SensorMCP9600::mcp9600_66;
MCP9600* SensorMCP9600::mcp9600_67;

SensorMCP9600::SensorMCP9600 (long id, String category, String shortName, String name, String i2cAdress, String sensorType, int refreshInterval, int postDataInterval, float smartValueThreshold, SensorCalculation* calculation) : Sensor (id, category, shortName, name, refreshInterval, postDataInterval, smartValueThreshold, calculation, false) {

  int i=0;
  failedInit = false;

  Wire.setClock(100000);

  if(i2cAdress=="0x67")
  {
	  if(mcp9600_67 == NULL)
	  {
		mcp9600_67 = new MCP9600();

		mcp9600_67->begin(0x67);

		while(!mcp9600_67->isConnected())
		{
			mcp9600_67->begin(0x67, Wire);
			Serial.println("Trying to find MCP9600 sensor at address 0x67!");
		    delay(500);

		    if(i==5)
		    {
			  Serial.println("Could not find a valid MCP9600 sensor at address 0x67, check wiring!");
			  failedInit=true;
			  return;
		    }
		    i++;
		}

		if(sensorType=="K") {
			mcp9600_67->setThermocoupleType(TYPE_K);
		}
		else if(sensorType=="J") {
			mcp9600_67->setThermocoupleType(TYPE_J);
		}
		else if(sensorType=="T") {
			mcp9600_67->setThermocoupleType(TYPE_T);
		}
		else if(sensorType=="N") {
			mcp9600_67->setThermocoupleType(TYPE_N);
		}
		else if(sensorType=="S") {
			mcp9600_67->setThermocoupleType(TYPE_S);
		}
		else if(sensorType=="E") {
			mcp9600_67->setThermocoupleType(TYPE_E);
		}
		else if(sensorType=="B") {
			mcp9600_67->setThermocoupleType(TYPE_B);
		}
		else if(sensorType=="R") {
			mcp9600_67->setThermocoupleType(TYPE_R);
		}

		mcp9600_67->setShutdownMode(NORMAL);

	  }
	  mcp = mcp9600_67;
  }
  else if(i2cAdress=="0x66")
  {
	  if(mcp9600_66 == NULL)
	  {
		mcp9600_66 = new MCP9600();

		mcp9600_66->begin(0x66);

		while(!mcp9600_66->isConnected())
		{
			mcp9600_67->begin(0x66, Wire);
			Serial.println("Trying to find MCP9600 sensor at address 0x66!");
		    delay(500);

		    if(i==5)
		    {
			  Serial.println("Could not find a valid MCP9600 sensor at address 0x66, check wiring!");
			  failedInit=true;
			  return;
		    }
		    i++;
		}

		if(sensorType=="K") {
			mcp9600_66->setThermocoupleType(TYPE_K);
		}
		else if(sensorType=="J") {
			mcp9600_66->setThermocoupleType(TYPE_J);
		}
		else if(sensorType=="T") {
			mcp9600_66->setThermocoupleType(TYPE_T);
		}
		else if(sensorType=="N") {
			mcp9600_66->setThermocoupleType(TYPE_N);
		}
		else if(sensorType=="S") {
			mcp9600_66->setThermocoupleType(TYPE_S);
		}
		else if(sensorType=="E") {
			mcp9600_66->setThermocoupleType(TYPE_E);
		}
		else if(sensorType=="B") {
			mcp9600_66->setThermocoupleType(TYPE_B);
		}
		else if(sensorType=="R") {
			mcp9600_66->setThermocoupleType(TYPE_R);
		}

		mcp9600_66->setShutdownMode(NORMAL);

	  }
	  mcp = mcp9600_66;
  }
  else
  {
	  if(mcp9600_60 == NULL)
	  {
		mcp9600_60 = new MCP9600();

		mcp9600_60->begin();

		while(!mcp9600_60->isConnected())
		{
			mcp9600_60->begin(0x60, Wire);
			Serial.println("Trying to find MCP9600 sensor at address 0x60!");
		    delay(500);

		    if(i==5)
		    {
			  Serial.println("Could not find a valid MCP9600 sensor at address 0x60, check wiring!");
			  failedInit=true;
			  return;
		    }
		    i++;
		}

		if(sensorType=="K") {
			mcp9600_60->setThermocoupleType(TYPE_K);
		}
		else if(sensorType=="J") {
			mcp9600_60->setThermocoupleType(TYPE_J);
		}
		else if(sensorType=="T") {
			mcp9600_60->setThermocoupleType(TYPE_T);
		}
		else if(sensorType=="N") {
			mcp9600_60->setThermocoupleType(TYPE_N);
		}
		else if(sensorType=="S") {
			mcp9600_60->setThermocoupleType(TYPE_S);
		}
		else if(sensorType=="E") {
			mcp9600_60->setThermocoupleType(TYPE_E);
		}
		else if(sensorType=="B") {
			mcp9600_60->setThermocoupleType(TYPE_B);
		}
		else if(sensorType=="R") {
			mcp9600_60->setThermocoupleType(TYPE_R);
		}

  		mcp9600_60->setShutdownMode(NORMAL);
	  }
	  mcp = mcp9600_60;
  }

}

void SensorMCP9600::preCycle(int cycleId)
{
}

Data* SensorMCP9600::read(bool shouldPostData)
{
  if(!isResetting && !failedInit)
  {
	if(_calculation->getValueUnit()=="°C")
    {
      float tempHotJunction = mcp->getThermocoupleTemp();
	  shouldPostData = smartSensorCheck(tempHotJunction, _smartValueThreshold, shouldPostData);
	  return _calculation->calculate(this, tempHotJunction, shouldPostData);
    }
    else if(_calculation->getValueUnit()=="K")
    {    
		float delta = mcp->getTempDelta();
		shouldPostData = smartSensorCheck(delta, _smartValueThreshold, shouldPostData);
		return _calculation->calculate(this, delta, shouldPostData);       
    }
    else if(_calculation->getValueType()=="pressure")
    {     
		float tempColdJunction = mcp->getAmbientTemp();
		shouldPostData = smartSensorCheck(tempColdJunction, _smartValueThreshold, shouldPostData);
		return _calculation->calculate(this, tempColdJunction, shouldPostData);
    }

  }
  return NULL;
}

boolean SensorMCP9600::smartSensorCheck(float currentRawValue, float threshhold, boolean shouldPostData)
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


