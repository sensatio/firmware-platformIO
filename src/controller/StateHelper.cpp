/**************************************************************************/
/*!
    @file     StateHelper.cpp
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

#include "StateHelper.h"

bool isWiFiConfigured()
{
  #ifdef ESP8266_BOARD
    EEPROM.begin(24);
  #endif

  int val20 = EEPROM.read(20);
  int val21 = EEPROM.read(21);
  int val22 = EEPROM.read(22);
  int val23 = EEPROM.read(23);

  #ifdef ESP8266_BOARD
    EEPROM.end();
  #endif

  if (val20 == 10 && val21 == 20 && val22 == 30 && val23 == 40)
  {
    #ifdef ESP8266_BOARD
      EEPROM.begin(24);
    #endif
    val20 = EEPROM.read(20);
    val21 = EEPROM.read(21);
    val22 = EEPROM.read(22);
    val23 = EEPROM.read(23);
    #ifdef ESP8266_BOARD
      EEPROM.end();
    #endif
  }
  if (val20 == 11 && val21 == 21 && val22 == 31 && val23 == 41)
    return true;
  else
    return false;
}