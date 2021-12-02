/**************************************************************************/
/*!
    @file     DisplayOLED128.h
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v41 - Renamed Display Class to support more types, New Display Mode
    v40 - New Display Structure to enable Display Rotation, different Styles etc.
    v33 - Added Digital Sensor Switch Support
    v30 - Added Support for SSD1306 Displays
    v29 - First Public Release
*/
/**************************************************************************/

#ifndef _DisplayOLED128_h_
#define _DisplayOLED128_h_

#include "Display.h"
#include "SSD1306Wire.h" 
#include "SH1106Wire.h"

class DisplayOLED128 : public Display {
  private:
    OLEDDisplay *display;
    int type;
  public:
    DisplayOLED128 (int, int, bool, int, String, uint8_t, uint8_t);
    void drawProductLogo();
    void clear(boolean update);
    void drawString(int16_t x, int16_t y, String text);
    void drawArrow();
    void blinkArrow(int count);
    void drawDisconnected(bool update);
    void drawConnected(bool update);
    void flip(int rotation);
    void drawData(unsigned long currentMillis);
    void clearValue(int position);
    void drawValue(int position, String name, String shortName, String value, String unit);
    void drawValueClassic(int position, String name, String shortName, String valueString);
    void drawValueClassicRA(int position, String name, String shortName, String valueString);
    void drawValueQuad(int position, String name, String shortName, String valueString);
    void clearValueClassic(int position);
    void clearValueQuad(int position);
    int getSimultanValueCount();
};

#endif
