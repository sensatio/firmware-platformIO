/**************************************************************************/
/*!
    @file     DisplayDataModel.cpp
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

#include "DisplayDataModel.h"

DisplayDataModel::DisplayDataModel ()
{
    _count = 0;
}

int DisplayDataModel::getCount()
{
    return _count;
}

void DisplayDataModel::setData(int position, DisplayValueData* newValueData)
{
    if(_count<=position)
    {
        _count=position+1;
        _displayValueData[position] = newValueData;
    }
}

void DisplayDataModel::updateData(int position, float value, String unit)
{
    if(position<_count)
        _displayValueData[position]->update(value, unit);
}

void DisplayDataModel::updateData(int position, boolean value, String unit)
{
    if(position<_count)
        _displayValueData[position]->update(value, unit);
}

void DisplayDataModel::updateData(int position, String value, String unit)
{
    if(position<_count)
        _displayValueData[position]->update(value, unit);
}

DisplayValueData* DisplayDataModel::getData(int position)
{
    if(position<_count)
        return _displayValueData[position];
    else
        return NULL;
}
