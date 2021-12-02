/**************************************************************************/
/*!
    @file     WiFiManager.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v41 - Renamed Display Class to support more types
    v29 - First Public Release
*/
/**************************************************************************/

#include "WiFiManager.h"

extern State state;
extern Display* display;
extern int powerMode;
extern int i2cSDAPort;
extern int i2cSCLPort;

#ifdef ESP8266_BOARD
  extern ESP8266WebServer http_rest_server;
#elif ESP32_BOARD
  extern WebServer http_rest_server;
#endif

IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

const char *myHostname = "sensateBridge";

DNSServer dnsServer;
const byte DNS_PORT = 53;

StaticJsonBuffer<10000> jsonBuffer;

void connectToNetwork()
{
	if(isWiFiConfigured())
	{
		connectToAP();
	}
	else
	{
		state = Init_AP;
		startUpLocalAP();
	}
	
}

void connectToAP() {

  Serial.println("Connecting to AP");

  #ifdef ESP8266_BOARD
    EEPROM.begin(121);
  #endif

  char ssidChars[33];
  char passwordChars[64];

  EEPROM.get(24, ssidChars);
  EEPROM.get(57, passwordChars);

  Serial.println("SSID: " + String(ssidChars));
  Serial.println("Password: ************");

  #ifdef ESP8266_BOARD
    EEPROM.end();
  #endif

  if(display!=NULL)
  {
    display->clear(true); 
    display->drawProductLogo();
    display->drawString(0, 5, "Connecting to...");
    display->drawString(0, 21, String(ssidChars));
  }

  #ifdef ESP32_BOARD
    WiFi.disconnect(true, true);
  #endif  

  WiFi.begin(ssidChars, passwordChars);

  Serial.println("Connecting to WiFi");
  int x = 0;

  int connRes = WiFi.waitForConnectResult();
  Serial.print("connRes: ");
  Serial.println(connRes);

  if(connRes==4)
  {
    Serial.println("Wait a little longer for WiFi to catch up..");
    delay(1000);
    yield();
    delay(1000);
    yield();
    delay(1000);
    yield();
    delay(1000);
    yield();
    delay(1000);
    yield();
  }
  
  if (WiFi.status() != WL_CONNECTED)
  {
    if(powerMode==2)
    {
      Serial.println("No WiFi connection possible, going back to Deep Sleep for 5 minutes.");
      trySleep(300000000);
    }
    else
    {
      Serial.println("Starting up Setup AP");
      state = Init_AP;
      startUpLocalAP();
    }
  }
  else
  {
    if(display!=NULL)
    {
      display->clear(true); 
      display->drawProductLogo();
      display->drawString(0, 5, "Joined:");
      display->drawString(0, 21, String(ssidChars));
    }

    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());
	  state = Check_Firmware;
  }
  
}

void checkWiFiStatus() {

  if (isWiFiConfigured() &&	WiFi.status() == WL_CONNECTED)
  {
    if(display!=NULL)
    {
      #ifdef ESP8266_BOARD
        EEPROM.begin(121);
      #endif
      char ssidChars[33];
      EEPROM.get(24, ssidChars);
      #ifdef ESP8266_BOARD
        EEPROM.end();
      #endif

      display->clear(true); 
      display->drawProductLogo();
      display->drawString(0, 5, "Joined:");
      display->drawString(0, 21, String(ssidChars));
    }

    Serial.println("softAPdisconnect()");
    WiFi.softAPdisconnect (true);

    Serial.println("Connected, IP address: ");
    Serial.println(WiFi.localIP());
	  state = Check_Firmware;
  }
}

bool startUpLocalAP() {

  Serial.println("Starting SoftAP 'Sensate-Setup'");

  #ifdef ESP8266_BOARD
    WiFi.softAPConfig(apIP, apIP, netMsk);
  #elif ESP32_BOARD
    WiFi.persistent(false);
  #endif
  
  WiFi.softAP("Sensate-Setup","Setup-Sensate");
  
  #ifdef ESP32_BOARD
    delay(2000);
    WiFi.softAPConfig(apIP, apIP, netMsk);
    delay(100);
  #endif

  int x = 0;
  while (WiFi.softAPIP().toString() == "0.0.0.0")
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Started, SoftAP IP address: ");
  Serial.println(WiFi.softAPIP());

  if(display!=NULL)
  {
    display->clear(true); 
    display->drawProductLogo();
    display->drawString(0, 5, "Please use App to");
    display->drawString(0, 21, "setup WiFi Network");
  }
  state = Init_Setup;
  return true;
}

void setupBridgeConfig() {

  Serial.println("REST POST /setupbridge");
  
  JsonObject& bridgeSettings = jsonBuffer.parseObject(http_rest_server.arg("plain"));

  String ssid = bridgeSettings["ssid"];
  String wifipassword = bridgeSettings["password"];
  String url = bridgeSettings["url"];
  String name = bridgeSettings["name"];
  String secPassword = bridgeSettings["secPassword"];

  if(display!=NULL)
  {
    display->clear(false);
    display->drawProductLogo();
    display->drawString(0, 5, "Connecting to...");
    display->drawString(0, 21, "'"+ssid+"'");
  }

  jsonBuffer.clear();

  if (ssid == "")
  {
    Serial.println("SSID Argument not found");
    http_rest_server.send(400);
    http_rest_server.client().stop();
  }
  else if (wifipassword == "")
  {
    Serial.println("Password Argument not found");
    http_rest_server.send(400);
    http_rest_server.client().stop();
  }
  else
  {
    http_rest_server.send(200);
    http_rest_server.client().stop();
    yield();
    
    char ssidChars[33];
    ssid.toCharArray(ssidChars, 33);
    char passwordChars[64];
    wifipassword.toCharArray(passwordChars, 64);
    char urlChars[100];
    url.toCharArray(urlChars, 100);
    
    #ifdef ESP8266_BOARD
      EEPROM.begin(289);
    #endif
    
    EEPROM.write(20, 11);
    EEPROM.write(21, 21);
    EEPROM.write(22, 31);
    EEPROM.write(23, 41);
    EEPROM.put(24, ssidChars);
    EEPROM.put(57, passwordChars);
    EEPROM.put(121, urlChars);

    if(name!="" || secPassword!="")
    {
      EEPROM.write(221, 221);
      EEPROM.write(222, 222);

      char nameChars[25];
      name.toCharArray(nameChars, 25);
      EEPROM.put(223, nameChars);
      
      //TODO: Fix for ESP32
      #ifdef ESP8266_BOARD
        if(secPassword!="")
        {
          char secPassChars[41];
          String shaSecPwd = sha1(secPassword);
          shaSecPwd.toCharArray(secPassChars, 41);
          EEPROM.put(248, secPassChars);
        }
        else
        {
          EEPROM.put(248, '\0');
        }
      #elif ESP32_BOARD
        EEPROM.put(248, '\0');
      #endif
    }
    #ifdef ESP8266_BOARD
      EEPROM.end();
    #elif ESP32_BOARD
      EEPROM.commit();

      delay(500);
      yield();
      delay(500);
      yield();
    #endif

    yield();

    restart();
  }

}

void setupBridgeConfigManual() {

Serial.println("REST POST /manualsetup");
  
  String ssid = http_rest_server.arg("ssid");
  String wifipassword = http_rest_server.arg("password");
  String url = http_rest_server.arg("url");
  String name = http_rest_server.arg("identifier");
  String secPassword = http_rest_server.arg("");

  if(display!=NULL)
  {
    display->clear(false);
    display->drawProductLogo();
    display->drawString(0, 5, "Connecting to...");
    display->drawString(0, 21, "'"+ssid+"'");
  }

  if (ssid == "")
  {
    Serial.println("SSID Argument not found");
    http_rest_server.send(400);
    http_rest_server.client().stop();
  }
  else if (wifipassword == "")
  {
    Serial.println("Password Argument not found");
    http_rest_server.send(400);
    http_rest_server.client().stop();
  }
  else
  {
    String wifiResponse = "<html><body style='width:600;margin-left:auto;margin-right:auto;font-family:verdana'><br/><br/><h1>Setup Complete - Bridge is restarting! Continue in App.</h1></body></html>";
    http_rest_server.send(200, "text/html", wifiResponse);
    http_rest_server.client().stop();
    yield();
    
    char ssidChars[33];
    ssid.toCharArray(ssidChars, 33);
    char passwordChars[64];
    wifipassword.toCharArray(passwordChars, 64);
    char urlChars[100];
    url.toCharArray(urlChars, 100);
    
    #ifdef ESP8266_BOARD
      EEPROM.begin(289);
    #endif
    EEPROM.write(20, 11);
    EEPROM.write(21, 21);
    EEPROM.write(22, 31);
    EEPROM.write(23, 41);
    EEPROM.put(24, ssidChars);
    EEPROM.put(57, passwordChars);
    EEPROM.put(121, urlChars);

    if(name!="" || secPassword!="")
    {
      EEPROM.write(221, 221);
      EEPROM.write(222, 222);

      char nameChars[25];
      name.toCharArray(nameChars, 25);
      EEPROM.put(223, nameChars);
      
      //TODO: Fix for ESP32
      #ifdef ESP8266_BOARD
        if(secPassword!="")
        {
          char secPassChars[41];
          String shaSecPwd = sha1(secPassword);
          shaSecPwd.toCharArray(secPassChars, 41);
          EEPROM.put(248, secPassChars);
        }
        else
        {
          EEPROM.put(248, '\0');
        }
      #elif ESP32_BOARD
        EEPROM.put(248, '\0');
      #endif
    }

    #ifdef ESP8266_BOARD
      EEPROM.end();
    #elif ESP32_BOARD
      EEPROM.commit();

      delay(500);
      yield();
      delay(500);
      yield();
    #endif

    yield();

    restart();
  }

}

void resetBridgeConfig() {

  Serial.println("REST GET /resetWiFi");

  #ifdef ESP8266_BOARD
    EEPROM.begin(296);
  #endif

  EEPROM.write(20, 0);
  EEPROM.write(21, 0);
  EEPROM.write(22, 0);
  EEPROM.write(23, 0);
  EEPROM.write(221, 0);
  EEPROM.write(222, 0);

  char nameChars[25] = "";
  EEPROM.put(223, nameChars);

  char pwdChars[41] = "";
  EEPROM.put(248, pwdChars);

  EEPROM.write(290, 0);
  EEPROM.write(291, 0);
  EEPROM.write(292, 0);
  EEPROM.write(293, 0);
  EEPROM.write(294, 0);
  EEPROM.write(295, 0);

  #ifdef ESP8266_BOARD
    EEPROM.end();
  #elif ESP32_BOARD
    EEPROM.commit();
  #endif

  http_rest_server.send(200);
  http_rest_server.client().stop();
  yield();

  restart();

}

void startDNS() {
  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(DNS_PORT, "*", apIP);

  if (!MDNS.begin(myHostname)) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.println("mDNS responder started");
    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);
  }

  state = Setup;
}

void shutDownWiFi() {
  Serial.println("shutDownWiFi()");

  yield();
  delay(1000);

  if(state==Setup)
    dnsServer.stop();

  yield();
  delay(1000);
  
  #ifdef ESP8266_BOARD
    WiFi.forceSleepBegin(); 
  #elif ESP32_BOARD
    WiFi.disconnect();
  #endif
}

void loopDNS() {

  dnsServer.processNextRequest(); 
      
  #ifdef ESP8266_BOARD
    if(WiFi.status()==WL_CONNECTED) {
      MDNS.update();
    }
  #endif

}