/**************************************************************************/
/*
    @file     SensatioFirmware.cpp
    @author   M. Fegerl (Sensate Digital Solutions GmbH)
    @license  GPL (see LICENSE file)
    The Sensatio firmware is used to connect ESP8266 and ESP32 based hardware
    with the Sensatio Cloud and the Sensatio apps.

    ----> https://www.sensatio.io

    SOURCE: https://github.com/sensatio/firmware-platformIO.git

    @section  HISTORY
    v46 - Merge of ESP8266 and ESP32 Firmware into PlatformIO project
    v45 - Fixed Pressure Measurement for BME280 Sensors
    v44 - More Memory Improvements
    v43 - Fixed data transmit issues in configurations with many sensors
    v42 - Fixed low memory issues in configurations with many sensors and a ST7735 Bug
    v41 - Changed IDE, Sensatio, Renamed Display Class to support more types
    v40 - New Display Structure to enable Display Rotation, different Styles etc.
    v39 - ReAdded Support for VEML6075 and SI1145 UVI Sensors, added auto-reinit if sensor fails
    v38 - Changed automatic Update to only if required Update, removed VEML6075 and SI1145 UV Sensors
    v36 - Greatly improved reliability of connectivity
    v35 - Added Support for VEML6075 and SI1145 UVI Sensors
    v34 - Added Generic Analog Sensor Support
    v33 - Added Digital Sensor Switch Support, Improved MQTT Setup Routine
    v32 - Added MQTT Support!
    v31 - Fixed an issue with DHT11 Sensors
    v30 - Added support for SSD1306 I2C Displays
    v29 - First Public Release
*/
/**************************************************************************/
#include "SensatioFirmware.h"

VisualisationHelper *vHelper;
Display *display = NULL;

int currentVersion = 46;
boolean printMemory = false;

#ifdef NodeMCU
  String board = "NodeMCU";
  char firmwareType[] = "ESP8266-NodeMCU";
#elif ESP01_1M
  String board = "Generic";
  char firmwareType[] = "ESP8266-1M";
#elif ESP07
  String board = "ESP07";
  char firmwareType[] = "ESP8266-ESP07";
#elif ESP12s
  String board = "ESP12s";
  char firmwareType[] = "ESP8266-ESP12s";
#elif D1_Mini
  String board = "D1Mini";
  char firmwareType[] = "ESP8266-D1Mini";
#elif ESP32_DevKitC
  String board = "DevKitC";
  char firmwareType[] = "ESP32-DevKitC";
#elif M5StickC
  String board = "M5StickC";
  char firmwareType[] = "ESP32-M5StickC";
#endif

String name = "Bridge";

#ifdef ESP8266_BOARD
  String ucType = "ESP8266";
#elif ESP32_BOARD
  String ucType = "ESP32";
#endif

String variant = "SensatioV" + String(currentVersion) + board;
String apiVersion = "v1";

int powerMode;
long powerOnDelay = 0;
String powerSavePort;
boolean invPowerSavePort = false;

bool isResetting = false;

unsigned long previousDelayMillis = 0;
unsigned long previousTickerMillis = 0;
unsigned long currentMillis;
State state = Boot;

int displayMode;
boolean displayEnabled;
int displayType;
int displayHeight;
int displayWidth;
int displayRotation;
bool firstSensorData;

#ifdef ESP8266_BOARD
  extern struct rst_info resetInfo;
#elif ESP32_BOARD
  esp_sleep_wakeup_cause_t resetInfo;
#endif

extern uint8_t i2cSDAPort;
extern uint8_t i2cSCLPort;
extern MQTT *mqtt;

extern String urlString;
extern String requestDataString;
extern String payload;

#define tickerInterval 250
#define delayInterval 10000

void setup()
{
  #ifdef ESP32_BOARD
    EEPROM.begin(398);
  #endif

  Serial.begin(9600);
  Serial.println("---------------------------");
  Serial.println(variant);
  Serial.println("---------------------------");
  Serial.println("Startup: ");
  Serial.println(getUUID()); // @suppress("Invalid arguments")

  urlString.reserve(300);
  requestDataString.reserve(200);
  payload.reserve(1000);

  restoreBridgeConfig();

  vHelper = new VisualisationHelper();

  doPowerSavingInit(true);

  Serial.println("Display Type:" + String(displayType));
  Serial.println("Display Enabled:" + String(displayEnabled));
  Serial.println("Display Rotation:" + String(displayRotation));
  Serial.println("Display Mode:" + String(displayMode));

  Serial.println("Power Mode:" + String(powerMode));
  Serial.println("Power On Delay:" + String(powerOnDelay));
  Serial.println("Power Save Port:" + String(powerSavePort));
  Serial.println("Power Save Port Inv:" + String(invPowerSavePort));

  if (displayType != 0)
  {
    boolean rotateDisplay = (displayRotation == 180);

    switch (displayType)
    {
    case 3:
      display = new DisplayST7735(rotateDisplay, displayType);
      break;
    default: // Fallback to OLED init
      display = new DisplayOLED128(displayWidth, displayHeight, rotateDisplay, displayType, "", i2cSDAPort, i2cSCLPort);
      break;
    }

    if (!displayEnabled)
      display->clear(true);
  }

  if (display != NULL)
    display->drawProductLogo();

  state = Connect_WiFi;

  initSensate();
}

void loop()
{
  if (!isResetting)
  {
    //First: Do whatever should be done in every loop!
    runLoop();

    //Then: Do short delayed actions (once every #tickerInterval miliseconds)
    currentMillis = millis();
    if (currentMillis - previousTickerMillis >= tickerInterval)
    {
      previousTickerMillis = currentMillis;
      runTick();
    }

    //Then: Do long delayed actions (once every #delayInterval miliseconds)
    currentMillis = millis();
    if (currentMillis - previousDelayMillis >= delayInterval)
    {
      previousDelayMillis = currentMillis;
      runDelayed();
    }
  }
}

void runLoop()
{
  switch (state)
  {
  case Setup:
    loopDNS();
    checkWiFiStatus();
  case Connected_WiFi:
  case Init_Configuration:
  case Operating:
    loopRestserver();
    if (mqtt != NULL)
      mqtt->loop();
    break;
  default:
    break;
  }
}

void runTick()
{
  // Serial.print("-T-");
  switch (state)
  {
  case Operating:
    loopDisplay(currentMillis);
    loopSensor(currentMillis);
    break;
  default:
    break;
  }

  if (printMemory)
  {
    Serial.print("HEAP: ");
    Serial.println(ESP.getFreeHeap());
  }

  if (ESP.getFreeHeap() < 1000)
  {
    Serial.println("RUNNING OUT OF HEAP - RESTART");
    restart();
  }
}

void runDelayed()
{
  // Serial.print("----D----");
  if (state != Operating)
    initSensate();
  else
    checkStatus();
}

void initSensate()
{

  if (state == Connect_WiFi)
  {
    Serial.println("STATE: Connect_WiFi");
    connectToNetwork();
  }
  if (state == Check_Firmware)
  {
    #ifdef ESP8266_BOARD
      if (resetInfo.reason != REASON_DEEP_SLEEP_AWAKE)
      {
        Serial.println("STATE: Check_Firmware");
        tryFirmwareUpdate("");
      }
      else
      {
        Serial.println("Skip Check_Firmware (Wake from Sleep)");
        state = Connected_WiFi;
      }
    #elif ESP32_BOARD
      switch (resetInfo)
      {
      case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Skip Check_Firmware (Wakeup caused by external signal using RTC_IO)");
        state = Connected_WiFi;
        break;
      case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Skip Check_Firmware (Wakeup caused by external signal using RTC_CNTL)");
        state = Connected_WiFi;
        break;
      case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Skip Check_Firmware (Wakeup caused by timer)");
        state = Connected_WiFi;
        break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Skip Check_Firmware (Wakeup caused by touchpad)");
        state = Connected_WiFi;
        break;
      case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Skip Check_Firmware (Wakeup caused by ULP program)");
        state = Connected_WiFi;
        break;
      default:
        Serial.println("STATE: Check_Firmware");
        tryFirmwareUpdate("");
        break;
      }
    #endif
    
  }
  if (state == Connected_WiFi)
  {
    Serial.println("STATE: Connected_WiFi");
    startRestServer();
  }
  if (state == Init_Setup)
  {
    Serial.println("STATE: Init_Setup");
    startRestServer();
    startDNS();
  }
  if (state == Register)
  {
    #ifdef ESP8266_BOARD
      initSSL();
      if (resetInfo.reason != REASON_DEEP_SLEEP_AWAKE)
      {
        Serial.println("STATE: Register_Bridge");
        registerBridge();
      }
      else
      {
        Serial.println("Skip Register_Bridge (Wake from Sleep)");
        state = Init_Configuration;
      } 
    #elif ESP32_BOARD
      switch (resetInfo)
      {
      case ESP_SLEEP_WAKEUP_EXT0:
        Serial.println("Skip Register_Bridge (Wakeup caused by external signal using RTC_IO)");
        state = Init_Configuration;
        break;
      case ESP_SLEEP_WAKEUP_EXT1:
        Serial.println("Skip Register_Bridge (Wakeup caused by external signal using RTC_CNTL)");
        state = Init_Configuration;
        break;
      case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("Skip Register_Bridge (Wakeup caused by timer)");
        state = Init_Configuration;
        break;
      case ESP_SLEEP_WAKEUP_TOUCHPAD:
        Serial.println("Skip Register_Bridge (Wakeup caused by touchpad)");
        state = Init_Configuration;
        break;
      case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("Skip Register_Bridge (Wakeup caused by ULP program)");
        state = Init_Configuration;
        break;
      default:
        Serial.println("STATE: Register_Bridge");
        registerBridge();
        break;
      }
    #endif
  }
  if (state == Init_Configuration)
  {
    Serial.println("STATE: Get_Configuration");
    getBridgeConfig();
  }
}