/**************************************************************************/
/*
    @file     SensatioFirmware.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v41 - Changed IDE, Sensatio
*/
/**************************************************************************/

// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section
#include "Arduino.h"

#ifndef _SensatioFirmware_H_
#define _SensatioFirmware_H_

#include "controller/Bridge.h"
#include "output/display/Display.h"
#include "communication/WiFiManager.h"
#include "controller/OTA.h"
#include "communication/RestServer.h"
#include "output/VisualisationHelper.h"

#ifdef ESP8266_BOARD
    #include <user_interface.h>
#elif ESP32_BOARD
    //Nothing to see here (yet)
#endif

void loop();
void runTick();
void runDelayed();
void runLoop();
void initSensate();

//Do not add code below this line
#endif /* _SensatioFirmware_H_ */