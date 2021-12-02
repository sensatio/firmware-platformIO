/**************************************************************************/
/*!
    @file     OTA.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v41 - Renamed Display Class to support more types
    v38 - Changed automatic Update to only if required Update
    v29 - First Public Release
*/
/**************************************************************************/

#include "OTA.h"

extern State state;
extern DisplayOLED128* display;

extern char firmwareType[];
extern int currentVersion; 

#ifdef ESP32_BOARD
  WiFiClient wifiClient;
#endif

void tryFirmwareUpdate(String fwUpdateToken) {

  t_httpUpdate_return ret;

  #ifdef ESP8266_BOARD
    ESPhttpUpdate.rebootOnUpdate(false);
  #endif

  Serial.println("Trying firmware Update...");
  
  if(display!=NULL)
  {
    display->clear(true);
    display->drawProductLogo();
    display->drawString(10, 5, "Trying Firmware");
    display->drawString(20, 21, "Update...");
  }

  String updatePath = "/v1/bridge/firmware/"+fwUpdateToken+"?version="+String(currentVersion)+"&type="+firmwareType;

  Serial.println(updatePath);
  
  #ifdef ESP8266_BOARD
    ret = ESPhttpUpdate.update("hub.sensate.cloud", 80, updatePath);
  #elif ESP32_BOARD
    ret = httpUpdate.update(wifiClient, "hub.sensate.cloud", 80, updatePath);
  #endif

  switch(ret) {
    case HTTP_UPDATE_FAILED:
        if(display!=NULL)
        {
          display->clear(false); 
          display->drawProductLogo();
        }
        Serial.println("[update] Update failed.");
        break;
    case HTTP_UPDATE_NO_UPDATES:
        if(display!=NULL)
        {
          display->clear(false); 
          display->drawProductLogo();
        }
        Serial.println("[update] Update no Update.");
        break;
    case HTTP_UPDATE_OK:
        if(display!=NULL)
        {
          display->clear(true); 
        }
        #ifdef ESP8266_BOARD
         restart();
        #endif
        Serial.println("[update] Update ok."); // may not called we reboot the ESP
        break;
  }

  if(state==Check_Firmware)
    state = Connected_WiFi;

}