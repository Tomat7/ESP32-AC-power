
void display_Oled()
{
#ifdef USE_OLED
	if ((millis() - msDisplay) > (SHOW_PERIOD - 100))
	{
		D(OLEDcore = xPortGetCoreID());
		LD.clearDisplay();
		char bufPnow[] = { "    " };
		char bufPset[] = { "    " };
		char cbuf[] = { "     " };
		const char *bufSpinner[] = { "\\", "|", "/", "-" };

		static int s;
		if ((s < 3) && (zcDetectedOK)) s++;
		else s = 0;
		LD.printString_12x16(bufSpinner[s], 0, 6);

		for (int i = 0; i < nSensor; i++)
		{
			dtostrf(dsTemp[i], 5, 1, cbuf);
			LD_printString_12x16(cbuf, 0, (i * 3));
			if (DS[i].Parasite) LD_printChar_6x8("`");
		}

		if (showPower)		// show P on display
		{
			dtostrf(Pnow, 4, 0, bufPnow);
			dtostrf(Pset, 4, 0, bufPset);
		}
		else				// show U&I on display
		{
			dtostrf(Unow, 4, 0, bufPnow);
			dtostrf((round(Inow * 100) / 100), 5, 2, bufPset);
			LD.printString_12x16("U", 68, 0);
		}

		if (zcDetectedOK || showPower)
		{
			LD.printString_12x16(bufPnow, 80, 0);
			LD.printString_12x16(bufPset, 80, 3);
		}
		else
		{
			LD.printString_12x16("-", 80, 0);
			LD.printString_12x16("-", 68, 3);
		}

		if (showSetMenu) LD.printString_12x16("_SET_", 69, 6);
		else if (!RemoteON) LD.printString_12x16("local", 69, 6);

#ifdef USE_MODBUS
		else if (mbMasterOK) LD.printString_12x16("MB_OK", 69, 6);
#else
		else if (mbMasterOK) LD.printString_12x16("Wi_Fi", 69, 6);
#endif
		else LD.printString_12x16(" _OFF", 69, 6);

		msDisplay = millis();
	}
#endif //USE_OLED
}


void print_Serial()
{
	PRINTLN("==================");
	PRINTF("Pset: ", Pset);
	PRINTF("Pnow: ", Pnow);
	PRINTF("Pweb: ", Pweb);
	PRINTF("Penc ", Pencoder);
	PRINTF("U = ", Unow);
	PRINTF("I = ", Inow, 3);
}

void print_Debug1()
{
	// DEBUG1 start
	DPRINTLN("==");
	DPRINTF("angle: ", _angle);
	//DPRINTLN("wifi: ", wifiConnectOK);
	DPRINTF("Ucounter: ", _Ucntr);
	DPRINTF("Icounter: ", _Icntr);
	DPRINTF("X2 ", X2);
	DPRINTF("RMScounter/sec: ", cntrRMS); //rmsCalcCounter = 0;
	DPRINTLN("+");

	D(PRINTF("ZCross/sec: ", _cntrZC);) //_zcCounter = 0;
		D(PRINTF("TriacInts/sec: ", _cntrTR);) //_trCounter = 0;
		D(PRINTF("TriacOpens/sec: ", _cntrTRopen);) //_trOpens = 0;
		D(PRINTF("TriacClose/sec: ", _cntrTRclose);) //_trOpens = 0;
		D(PRINTF("TimerOpen: ", tmrOpen);) //_tmrRead = 0;
		D(PRINTF("TimerClose: ", tmrClose);) //_tmrRead = 0;
		D(PRINTLN("--");)
}

void print_Debug2()
{
	// DEBUG2 start
	//DPRINTF("_Summ ", int(_summ));	// ?? wtf
	//DPRINTF("_U ", (sqrt((float)_summ / (float)_cntr) * U_RATIO));  // ?? wtf
	D(PRINTF("Umax: ", adcUmax);)
		D(PRINTF("Imax: ", adcImax);)
		D(PRINTLN("--");)

		D(PRINTF("INFO core ", INFOcore);)
		D(PRINTF("OLED core ", OLEDcore);)

		D(PRINTF("RMS core ", RMScore);)
		D(PRINTF("RMS prio ", RMSprio);)
		D(PRINTF("ZCROSS core ", ZCcore);)
		D(PRINTF("ZCROSS prio ", ZCprio);)
		D(PRINTF("TRIAC core ", TRIACcore);)
		D(PRINTF("TRIAC prio ", TRIACprio);)
		D(PRINTF("PRINT core ", xPortGetCoreID());)
		D(PRINTF("PRINT prio ", uxTaskPriorityGet(NULL));)
		D(PRINTF("ADC core ", ADCcore);)
		D(PRINTF("ADC prio ", ADCprio);)
		D(PRINTLN("--");)

		D(PRINTF("ZCdn duration ", usZCduration);)
		D(PRINTF("ZCtoTRIAC ", usZCtoTRIAC);)
		D(PRINTF("TRIAC open uSec ", usTRopen);)
		//D(PRINTF("portTICK_PERIOD ", portTICK_PERIOD_MS);)
		//DPRINTF("local_buf ", Pencoder);
		// DEBUG end
		PRINTF("DisplayPeriod(ms): ", (millis() - msPrint));
}
