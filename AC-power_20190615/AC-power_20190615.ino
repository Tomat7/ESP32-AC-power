#define VERSION_CODE "124"
#include "config.h"
#include "config_wifi.h"
#include "config_libs.h"
#include "variables.h"
#include "macros.h"
//#include "esp_task_wdt.h"

void setup()
{
	strVersion = SKETCHINFO;

	setup_SerialOLED();
	setup_Encoder();
	setup_Network();
	setup_OTA();
	setup_Web();
	setup_Modbus();
	TEH.init(I_RATIO, U_RATIO);
	TEH.adjustRMS(NULL, Ucorr);

	/*
	setup_Triac();
	setup_ZeroCross();
	setup_ADC();
	*/

	setup_DS();

	//setup_RMS();

	delay(1000);
	PRINTLN("+ READY to work.");

#ifdef TASK_INFO
	setup_InfoTask();
#endif
}

void loop()
{
	//if (xSemaphoreTake(smphRMS, 0) == pdTRUE) { update_RMS(); }
	TEH.control();

#ifdef TASK_INFO
	display_Oled();
#else
	update_Info();
#endif // !TASK_SHOW

#ifdef USE_MODBUS
	mb.task();
#endif
#ifdef USE_OTA
	ArduinoOTA.handle();
#endif
#ifdef USE_WEBSERVER
	server.handleClient();
#endif
#ifdef USE_ENCODER
	check_Encoder();
#endif
}
