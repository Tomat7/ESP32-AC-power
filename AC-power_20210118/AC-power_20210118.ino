#define VERSION_CODE "139"
#include "config.h"
#include "config_wifi.h"
#include "config_libs.h"
#include "variables.h"
#include "macros.h"

void setup()
{
	strVersion = SKETCHINFO;
	strConfig += String(__FILE__) + "\r\n";
	strConfig += String(" . Compiled on: ") + __DATE__ + String(" ") + __TIME__ + "\r\n";
	Serial.begin(115200);
	delay(1000);

	setup_SerialOLED();
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

	log_cfg_f(" . Free memory: ", String(ESP.getFreeHeap()));
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
