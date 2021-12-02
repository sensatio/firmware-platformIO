/**************************************************************************/
/*!
    @file     DisplayDataModel.h
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

#include <Arduino.h>
#include "DisplayValueData.h"

#define maxSensorCount 25

#ifndef _DISPLAYDATAMODEL_h_
#define _DISPLAYDATAMODEL_h_

class DisplayDataModel {
  private:
    int _count;
    DisplayValueData* _displayValueData[maxSensorCount];
  public:
    DisplayDataModel ();
    int getCount();
    void setData(int, DisplayValueData*);
    void updateData(int, float, String);
    void updateData(int, boolean, String);
    void updateData(int, String, String);
    DisplayValueData* getData(int);
};

#endif