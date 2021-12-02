/**************************************************************************/
/*!
    @file     VisualisationHelper.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v40 - New Display Structure to enable Display Rotation, different Styles etc.
*/
/**************************************************************************/

#include "VisualisationHelper.h"

VisualisationHelper::VisualisationHelper()
{
    _displayDataModel = new DisplayDataModel();
}

DisplayDataModel* VisualisationHelper::getDisplayDataModel()
{
    return _displayDataModel;
}

void VisualisationHelper::enableDisplayCycle(unsigned long currentMillis, int simultanValueCount, unsigned long interval)
{
    if(!_enableCycle && (_displayDataModel->getCount()>simultanValueCount))
    {
        _enableCycle = true;
        _lastDisplayCycleUpdate = currentMillis;

        _simultanValueCount = simultanValueCount;
        _displayCycleInterval = interval;
        
        int dataCount = _displayDataModel->getCount();
        _maxCyclePosition = dataCount/simultanValueCount;
        if(dataCount%simultanValueCount==0)
            _maxCyclePosition--;

        Serial.println("Display Cycle enabled with "+String(_maxCyclePosition+1)+" screens showing "+String(simultanValueCount)+" values on each.");
    }
}

void VisualisationHelper::disableDisplayCycle()
{
    _enableCycle = false;
    _currentCyclePosition = 0;
}
    
DisplayValueData* VisualisationHelper::getDataForPosition(unsigned long currentMillis, int position)
{
    if(_displayDataModel!=NULL)
    {
        if(!_enableCycle)
        {
            return _displayDataModel->getData(position);
        }
        else
        {
            if(currentMillis > _lastDisplayCycleUpdate+_displayCycleInterval || currentMillis < _lastDisplayCycleUpdate)
            {
                _lastDisplayCycleUpdate = currentMillis;

                if(_currentCyclePosition<_maxCyclePosition)
                    _currentCyclePosition++;
                else
                    _currentCyclePosition=0;
            }

            int pos = position + (_currentCyclePosition*_simultanValueCount);
            return _displayDataModel->getData(pos);
        }
    }

    return NULL;
}

void VisualisationHelper::updateSimultanValueCount(int simultanValueCount)
{
	_simultanValueCount = simultanValueCount;
	disableDisplayCycle();
	enableDisplayCycle(_lastDisplayCycleUpdate, _simultanValueCount, _displayCycleInterval);
}

