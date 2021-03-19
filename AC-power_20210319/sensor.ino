
void setup_DS()
{
#ifdef USE_DS18B20
	LD_printString_6x8("DS on pin: ", LCDX1, 7);

	for (int i = 0; i < nSensor; i++)
	{
		DS[i].init(DS_CONVTIME);
		mb.addHreg(hrDSTEMP + i);                // Модбас регистр - значение температуры
		int pins[] = PIN_DS;
		LD_printNumber((long)pins[i]);
		if (i < (nSensor - 1)) LD_printChar_6x8(", ");
#ifdef SERIAL_CONFIG
		// DS[i].printConfig();
		String dsOK;
		if (DS[i].Connected) dsOK = "+ ";
		else dsOK = "-- ";
		dsOK += "DS " + String(i) + ": ";
		log_cfg_ln(dsOK, DS[i].LibConfig);
		// String sInfo = ".  ID " + String(i, DEC) + " | Connected " + String(DS[i].Connected, DEC);
		// CPRINTLN(sInfo);
#endif	// SERIAL_CONFIG
	}
#endif	// USE_DS18B20
}

void update_DS()
{
#ifdef USE_DS18B20

	for (int i = 0; i < nSensor; i++)
	{
#ifdef DS_ERRORS
		if ((cntrDSerrors > 0) && (cntrDSerrors < DS_ERRORS))
		{
			cntrDSerrors++;
			return;
		}
		else if (cntrDSerrors == DS_ERRORS) 
		{
			DS[i].init(DS_CONVTIME);
			cntrDSerrors++;
			return;
		}
		else
		{
			DS[i].check();
		}

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
		DS[i].check();
		dsTemp[i] = DS[i].Temp;
#endif	// DS_ERRORS

#ifdef SERIAL_INFO
		String dsInfo = ".  DS " + String(i, DEC) + ": " + String(dsTemp[i], 2) + " | parasite: " +
			String(DS[i].Parasite, DEC) + " | " + String(DS[i].TimeConv, DEC);
		if (showInfo > 0) log_info_ln(dsInfo);
#endif	// SERIAL_INFO
	}
#endif	// USE_DS18B20
}
