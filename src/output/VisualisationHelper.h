/**************************************************************************/
/*!
    @file     VisualisationHelper.h
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
#include "model/DisplayDataModel.h"

#ifndef _VISUALISATIONHELPER_h_
#define _VISUALISATIONHELPER_h_

class VisualisationHelper {
  private:
    DisplayDataModel* _displayDataModel;
    boolean _enableCycle = false;
    unsigned long _displayCycleInterval;
    int _simultanValueCount;
    unsigned long _lastDisplayCycleUpdate;
    int _currentCyclePosition = 0;
    int _maxCyclePosition = 0;
  public:
    VisualisationHelper();
    DisplayDataModel* getDisplayDataModel();
    void enableDisplayCycle(unsigned long, int, unsigned long);
    void disableDisplayCycle();
    DisplayValueData* getDataForPosition(unsigned long, int);
    void updateSimultanValueCount(int);
};

#endif
