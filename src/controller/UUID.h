/**************************************************************************/
/*!
    @file     UUID.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v29 - First Public Release
*/
/**************************************************************************/

#ifndef _UUID_H_
#define _UUID_H_

#include <EEPROM.h>
#include "thirdparty/ESPTrueRandom.h"

String getUUID();
void restoreUUID();
void generateUUID();

#endif
