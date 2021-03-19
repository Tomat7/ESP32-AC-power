#define VERSION_CODE "143"
#include "config.h"
#include "config_wifi.h"
#include "config_libs.h"
#include "variables.h"
#include "macros.h"
#include "core_version.h"

void setup()
{
//  strConfig += String(__FILE__) + "\r\n";
//  strConfig += String(" . compiled on ") + __DATE__ + String(" ") + __TIME__ + "\r\n";
//  strConfig += String(" . by ESP32 Arduino core ") + ARDUINO_ESP32_RELEASE + " with ESP-IDF " + ESP.getSdkVersion() + "\r\n";
//  strConfig += String(" . version: ") + VERSION_CODE + "\r\n";
  log_cfg_ln(String(__FILE__));
  log_cfg_ln(String(" . compiled on ") + __DATE__ + String(" ") + __TIME__);
  log_cfg_ln(String(" . by ESP32 Arduino core ") + ARDUINO_ESP32_RELEASE + " with ESP-IDF " + ESP.getSdkVersion());
  log_cfg_ln(String(" . version: ") + VERSION_CODE);
  strVersion = SKETCHINFO;

  setup_Serial();
  setup_Display();
  setup_Encoder();
  setup_Network();
  setup_OTA();
  setup_Web();
  setup_Telnet();
  setup_Modbus();

  delay(2000);
  setup_PinInfo();
  setup_DS();

  //TEH.init(I_RATIO, U_RATIO);	// = init() + initADC() + setRMSratio(I_RATIO, U_RATIO);
  TEH.init();						// = init() + initADC() + setRMSratio(0.02, 0.2);
  TEH.setRMScorrection(NULL, Ucorr);
  log_cfg_addstr(TEH.LibConfig);

  log_cfg_ln(" . Free memory: ", String(ESP.getFreeHeap()));
  delay(2000);
  log_cfg_ln("+ READY to work.");

#ifdef USE_TASK_INFO
  setup_InfoTask();
#endif
}

void loop()
{
  LD_DEBUGM("TC");
  TEH.control();
  //TEH.control(4000);  // ручное управление углом!

#ifdef USE_TASK_INFO
  display_Oled();
#else
  LD_DEBUGM("UI");
  update_Info();
#endif // !TASK_SHOW

#ifdef USE_MODBUS
  LD_DEBUGM("MT");
  mb.task();
#endif
#ifdef USE_OTA
  LD_DEBUGM("OT");
  ArduinoOTA.handle();
#endif
#ifdef USE_WEBSERVER
  LD_DEBUGM("WS");
  httpd.handleClient();
#endif
#ifdef USE_TELNET
  check_Telnet();
#endif
#ifdef USE_ENCODER
  LD_DEBUGM("EN");
  check_Encoder();
#endif
}
