void setup_Serial()
{
#ifdef SERIAL_CONFIG
	Serial.begin(115200);
	delay(1000);
	Serial.print(strConfig);
#endif
}

void setup_Encoder()
{
#ifdef USE_ENCODER
	key.add_key(ENCODER_pSW);
	key.add_enccoder(ENCODER_pCLK, ENCODER_pDT);
	log_cfg_ln("+ ENCODER configured OK.");
#else 
	log_cfg_ln("-- NO ENCODER in this version.");
#endif
}




void setup_PinInfo()
{
#ifdef USE_3PHASE
	uint8_t pins[3][4] = { PINS_PHASE0, PINS_PHASE1, PINS_PHASE2 };
	uint8_t phases = 3;
#else
	uint8_t pins[1][4] = { PIN_ZCROSS, PIN_TRIAC, PIN_I, PIN_U };
	uint8_t phases = 1;
#endif

	LD_clearDisplay();
	String strVer;
	strVer = TEH.LibVersion;
	char chVer[21];
	strVer.toCharArray(chVer, 21);
	LD_printString_6x8(chVer, LCDX1, 0);
	LD_printString_6x8(" pins: ZC  TR  I   U", LCDX1, 1);

	for (int i = 0; i < phases; i++)
	{
		LD_printString_6x8("phase", LCDX1, i + 2);
		LD_printNumber((long)i);
		LD_printChar_6x8(" ");
		for (int j = 0; j < 4; j++)
		{
			LD_printNumber((long)pins[i][j]);
			if (j < 3) LD_printChar_6x8(", ");
		}
	}

}


void setup_InfoTask()
{
#ifdef USE_TASK_INFO
	xTaskCreatePinnedToCore(
		Info_task,	// Function to implement the task
		"INFOtask",	// Name of the task
		10000,      // Stack size in words
		NULL,       // Task input parameter
		0,          // Priority of the task
		&taskInfo,   // Task handle
		0);			// Core where the task should run
	log_cfg_ln("+ SHOW TASK setup OK");
#endif
}
