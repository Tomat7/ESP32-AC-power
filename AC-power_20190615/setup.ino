
void setup_InfoTask()
{
#ifdef TASK_INFO
	xTaskCreatePinnedToCore(
		Info_task,	// Function to implement the task
		"INFOtask",	// Name of the task
		10000,      // Stack size in words
		NULL,       // Task input parameter
		0,          // Priority of the task
		&taskInfo,   // Task handle
		0);			// Core where the task should run
	PRINTLN("+ SHOW TASK setup OK");
#endif
}

void setup_Network()   //Config Modbus IP
{
	initETH();
	check_WiFi();
	if (!wifiErrors) { PRINTLN("+ WiFi connected!"); }
	else { PRINTLN("-- WiFi NOT FOUND! Will try to connect later."); }
	serialIP();
	displayIP();
	if (!wifiErrors) { PRINTLN("+ WiFi setup OK"); }
	else { PRINTLN("-- WiFi setup finished with ERROR"); }
}

void setup_SerialOLED()
{
	Serial.begin(115200);
	LD_init();
	LD_clearDisplay();
	delay(1000);

	PRINTLN(strVersion);
	PRINTF(".  VERSION: ", VERSION_CODE);
	String strVer = strVersion.substring(1 + strVersion.lastIndexOf('\\'));
	char chVer[16];
	strVer.toCharArray(chVer, 16);
	LD_printString_6x8(chVer, LCDX1, 0);
#ifndef USE_OLED
	PRINTLN("-- NO OLED in this version.");
#endif
}

void setup_Encoder()
{
#ifdef USE_ENCODER
	key.add_key(ENCODER_pSW);
	key.add_enccoder(ENCODER_pCLK, ENCODER_pDT);
	PRINTLN("+ ENCODER configured OK.");
#else 
	PRINTLN("-- NO ENCODER in this version.");
#endif
}
