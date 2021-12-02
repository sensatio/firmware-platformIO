/**************************************************************************/
/*!
    @file     valuetype.h
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

#ifndef _valuetype_h_
#define _valuetype_h_

typedef enum 
{
  FLOAT,
  BOOL,
  STRING
} valuetype;

#endif