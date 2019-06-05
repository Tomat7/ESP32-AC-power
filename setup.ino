
void setup_Triac()
{
	DELAYx;
	pinMode(PIN_TRIAC, OUTPUT);
	_angle = 0; // MAX_OFFSET;
	smphTriac = xSemaphoreCreateBinary();
	timerTriac = timerBegin(0, 80, true);
	timerAttachInterrupt(timerTriac, &OpenTriac_int, true);
	timerAlarmWrite(timerTriac, (ANGLE_MAX + ANGLE_DELTA), true);
	timerAlarmEnable(timerTriac);
	timerWrite(timerTriac, _angle);
	PRINTLN("+ TRIAC setup OK");
}

void setup_ZeroCross()
{
	DELAYx;
	takeADC = false;
	_msZCmillis = millis();
	smphRMS = xSemaphoreCreateBinary();
	smphZC = xSemaphoreCreateBinary();
	pinMode(PIN_ZCROSS, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(PIN_ZCROSS), ZeroCross_int, ZC_EDGE);
	PRINTLN("+ ZeroCross setup OK");
}

void setup_ADC()
{
	DELAYx;
	usADCinterval = (uint16_t)(10000 / ADC_RATE);
	ADCperSet = ADC_RATE * ADC_WAVES;
	smphADC = xSemaphoreCreateBinary();
#ifdef TASK_ADC
	xTaskCreatePinnedToCore(
		GetADC_task,// Function to implement the task
		"ADCtask",	// Name of the task
		10000,      // Stack size in words
		NULL,       // Task input parameter
		0,          // Priority of the task
		&taskADC,   // Task handle
		0);			// Core where the task should run
	PRINTLN("+ ADC TASK setup OK");
#else
	timerADC = timerBegin(1, 80, true);
	timerAttachInterrupt(timerADC, &GetADC_int, true);
	timerAlarmWrite(timerADC, usADCinterval, true);
	timerAlarmEnable(timerADC);
	PRINTLN("+ ADC Inerrupt setup OK");
	PRINTF(".  ADC microSeconds between samples: ", usADCinterval);
	PRINTF(".  ADC samples per half-wave: ", ADC_RATE);
	PRINTF(".  ADC samples per calculation set: ", ADCperSet);
#endif
	PRINTF(".  ADC half-waves per calculation set: ", ADC_WAVES);
}

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
