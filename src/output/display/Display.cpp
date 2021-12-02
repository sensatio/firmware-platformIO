/**************************************************************************/
/*!
    @file     Display.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v41 - Abstract Display Class to support more types
*/
/**************************************************************************/

#include "Display.h"

extern VisualisationHelper* vHelper;

Display::Display(int _type) {

  type = _type;
  visibleDataCount = 0;

}

void Display::clear(boolean update) {
}

void Display::drawProductLogo() {
}

void Display::drawData(unsigned long currentMillis) {
}

void Display::drawString(int16_t x, int16_t y, String text) {
}

void Display::drawDisconnected(bool update) {

}

void Display::drawConnected(bool update) {

}

void Display::flip(int rotation) {

}

int Display::getType() {
	return type;
}

int Display::getSimultanValueCount() {
	return visibleDataCount;
}
