void display_Oled()
{
#ifdef USE_OLED
	if ((millis() - msDisplay) > (SHOW_PERIOD - 100))
	{
		D(OLEDcore = xPortGetCoreID());
		LD.clearDisplay();
		display_OledSpinner();
		display_OledTemp();
		display_OledPower(TEH.Pset);
		display_OledStatus();
		msDisplay = millis();
	}
#endif //USE_OLED
}

void display_OledTemp()
{
#ifdef USE_OLED
	char cbuf[] = { "     " };
	//check_WiFi();
	dtostrf(wifiErrors, 3, 0, cbuf);
	LD_printString_12x16(cbuf, 0, 3);

	for (int i = 0; i < nSensor; i++)
	{
		dtostrf(dsTemp[i], 5, 1, cbuf);
		LD_printString_12x16(cbuf, 0, (i * 3));
		if (DS[i].Parasite) LD_printChar_6x8("`");
		else LD_printChar_6x8(" ");
	}
#endif //USE_OLED
}

void display_OledPower(uint16_t Pshow)
{
#ifdef USE_OLED
	char bufPnow[] = { "     " };
	char bufPset[] = { "     " };

	if (showPower)		// show P on display
	{
		dtostrf(TEH.Pnow, 4, 0, bufPnow);
		dtostrf(Pshow, 4, 0, bufPset);
	}
	else				// show U&I on display
	{
		dtostrf(TEH_UNOW, 4, 0, bufPnow);
		//dtostrf((round(TEH.Inow * 100) / 100), 5, 2, bufPset);
		dtostrf(TEH_INOW, 5, 2, bufPset);
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
#endif //USE_OLED
}

void display_OledSpinner()
{
#ifdef USE_OLED
	const char *bufSpinner[] = { "\\", "|", "/", "-" };
	static int s;

	if ((s < 3) && (zcDetectedOK)) s++;
	else s = 0;
	LD.printString_12x16(bufSpinner[s], 0, 6);
#endif //USE_OLED
}

void display_OledStatus()
{
#ifdef USE_OLED
	if (showSetMenu) LD.printString_12x16("_SET_", 69, 6);
	else if (!RemoteON) LD.printString_12x16("local", 69, 6);

#ifdef USE_MODBUS
	else if (mbMasterOK) LD.printString_12x16("MB_OK", 69, 6);
#else
	else if (wifiErrors == 0) LD.printString_12x16("Wi_Fi_OK", 69, 6);
#endif
	else LD.printString_12x16(" _OFF", 69, 6);
#endif //USE_OLED
}

