
void display_Oled()
{
#ifdef USE_OLED
	if ((millis() - msDisplay) > (SHOW_PERIOD - 100))
	{
		D(OLEDcore = xPortGetCoreID());
		LD.clearDisplay();
		char bufPnow[] = { "     " };
		char bufPset[] = { "     " };
		char cbuf[] = { "     " };
		const char *bufSpinner[] = { "\\", "|", "/", "-" };

		static int s;
		if ((s < 3) && (zcDetectedOK)) s++;
		else s = 0;
		LD.printString_12x16(bufSpinner[s], 0, 6);

		check_WiFi();
		dtostrf(wifiErrors, 5, 1, cbuf);
		LD_printString_12x16(cbuf, 0, 3);

		for (int i = 0; i < nSensor; i++)
		{
			dtostrf(dsTemp[i], 5, 1, cbuf);
			LD_printString_12x16(cbuf, 0, (i * 3));
			if (DS[i].Parasite) LD_printChar_6x8("`");
		}

		if (showPower)		// show P on display
		{
			dtostrf(TEH.Pnow, 4, 0, bufPnow);
			dtostrf(TEH.Pset, 4, 0, bufPset);
		}
		else				// show U&I on display
		{
			dtostrf(TEH.Unow, 4, 0, bufPnow);
			//dtostrf((round(TEH.Inow * 100) / 100), 5, 2, bufPset);
			dtostrf(TEH.Inow, 5, 2, bufPset);
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
	PRINTF("Pset: ", TEH.Pset);
	PRINTF("Pnow: ", TEH.Pnow);
	PRINTF("Pweb: ", Pweb);
	PRINTF("Penc ", Pencoder);
	PRINTF("U = ", TEH.Unow);
	PRINTF("I = ", TEH.Inow, 3);
}

void print_Debug1()
{
	// DEBUG1 start
	DPRINTLN("==");
	DPRINTF("angle: ", TEH.Angle);
	//DPRINTLN("wifi: ", wifiConnectOK);
	DPRINTF("Ucounter: ", TEH._Ucntr);
	DPRINTF("Icounter: ", TEH._Icntr);
	DPRINTF("X2 ", TEH.X2);
	DPRINTF("RMScounter/sec: ", TEH.CounterRMS); //rmsCalcCounter = 0;
	DPRINTLN("+");

	D(PRINTF("ZCross/sec: ", TEH.CounterZC);) //_zcCounter = 0;
		D(PRINTF("TriacInts/sec: ", TEH.CounterTR);) //_trCounter = 0;
		D(PRINTF("TriacOpens/sec: ", TEH.CounterTRopen);) //_trOpens = 0;
		D(PRINTF("TriacClose/sec: ", TEH.CounterTRclose);) //_trOpens = 0;
		D(PRINTF("TimerOpen: ", TEH.TimerTRopen);) //_tmrRead = 0;
		D(PRINTF("TimerClose: ", TEH.TimerTRclose);) //_tmrRead = 0;
		D(PRINTLN("--");)
}

void print_Debug2()
{
	// DEBUG2 start
	//DPRINTF("_Summ ", int(_summ));	// ?? wtf
	//DPRINTF("_U ", (sqrt((float)_summ / (float)_cntr) * U_RATIO));  // ?? wtf
	//D(PRINTF("Umax: ", adcUmax);)
	//	D(PRINTF("Imax: ", adcImax);)
	D(PRINTLN("--");)

		D(PRINTF("INFO core ", INFOcore);)
		D(PRINTF("OLED core ", OLEDcore);)

		D(PRINTF("RMS core ", TEH.RMScore);)
		D(PRINTF("RMS prio ", TEH.RMSprio);)
		D(PRINTF("ZCROSS core ", TEH.ZCcore);)
		D(PRINTF("ZCROSS prio ", TEH.ZCprio);)
		D(PRINTF("TRIAC core ", TEH.TRIACcore);)
		D(PRINTF("TRIAC prio ", TEH.TRIACprio);)
		D(PRINTF("ADC core ", TEH.ADCcore);)
		D(PRINTF("ADC prio ", TEH.ADCprio);)
		D(PRINTF("PRINT core ", xPortGetCoreID());)
		D(PRINTF("PRINT prio ", uxTaskPriorityGet(NULL));)

		D(PRINTLN("--");)

		//D(PRINTF("ZCdn duration ", usZCduration);)
		//D(PRINTF("ZCtoTRIAC ", usZCtoTRIAC);)
		//D(PRINTF("TRIAC open uSec ", usTRopen);)
		//D(PRINTF("portTICK_PERIOD ", portTICK_PERIOD_MS);)
		//DPRINTF("local_buf ", Pencoder);
		// DEBUG end
		PRINTF("DisplayPeriod(ms): ", (millis() - msPrint));
}
