
void setup_DS()
{
#ifdef USE_DS18B20
	LD_printString_6x8("DS on pin: ", LCDX1, 5);

	for (int i = 0; i < nSensor; i++)
	{
		DS[i].init(DS_CONVTIME);
		mb.addHreg(hrDSTEMP + i);                // Модбас регистр - значение температуры
		int pins[] = PIN_DS;
		LD_printNumber((long)pins[i]);
		if (i < (nSensor - 1)) LD_printChar_6x8(", ");
#ifdef SERIAL_CONFIG
		DS[i].printConfig();
		String sInfo = "ID " + String(i, DEC) + "|Connected " + String(DS[i].Connected, DEC);
		PRINTLN(sInfo);
#endif
	}
#endif
}

void update_DS()
{
#ifdef USE_DS18B20
	for (int i = 0; i < nSensor; i++)
	{
		DS[i].check();
#ifdef DS_ERRORS
		float t = DS[i].Temp;
		if (t > DS_MIN_T)
		{
			dsTemp[i] = t;
			cntrDSerrors = 0;
		}
		else if (cntrDSerrors > DS_ERRORS)
		{
			dsTemp[i] = t;
			cntrDSerrors++;
		}
		else 
		{
			cntrDSerrors++;
		}
#else
		dsTemp[i] = DS[i].Temp;
#endif
		String dsInfo = ".  DS " + String(i, DEC) + ": " + String(dsTemp[i], 2) + " | parasite: " +
			String(DS[i].Parasite, DEC) + " | " + String(DS[i].TimeConv, DEC);
		PRINTLN(dsInfo);
	}
#endif
}
