/*
void setup_RMS()
{
	char zbuf[] = { "     " };
	float Uzerolevel, Izerolevel;
	uint16_t Ucntr, Icntr;
	uint16_t Ucycles = 30;
	Pset = 0;
	PRINTLN(".  RMS trying to calibrate...");
	LD_printString_6x8("Calibrating...", 2, 7);

	do 
	{
		rmsCalibrated = false;
		Uzerolevel = 0; Izerolevel = 0;
		Ucntr = 0; Icntr = 0;
		delay(500);
		check_ZeroCross();
		if (zcDetectedOK)
		{
			PRINTF("+ RMS ZERO-crossing detected: ", _cntrZC);
			PRINTLN("+ RMS calculating ZERO-shift for U and I...");
			LD_printString_6x8("ZC ok", 95, 7);
			while (Ucntr < Ucycles)
			{
				if (xSemaphoreTake(smphRMS, 0) == pdTRUE)
				{
					update_RMS();
					if (getI) { Uzerolevel += Unow / U_RATIO; Ucntr++; }
					else { Izerolevel += Inow / I_RATIO; Icntr++; }
				}
				else
				{
					delay(10);
#ifdef USE_ENCODER
					key.readkey();
#endif
					//esp_task_wdt_reset();
				}
			}
			rmsCalibrated = true;
			Uzerolevel /= Ucntr;
			Izerolevel /= Icntr;
		}
		else
		{
			PRINTLN("-- RMS NO ZERO-crossing DETECTED!");
			PRINTLN("-- RMS default values loaded.");
			LD_printString_6x8("ERROR", 92, 7);
			Uzerolevel = U_ZERO;
			Izerolevel = I_ZERO;
		}
		Unow = 0;
		Inow = 0;
		Ucycles = 10;
		PRINTF(".  RMS ZeroLevel U: ", Uzerolevel);
		PRINTF(".  RMS ZeroLevel  I: ", Izerolevel);
		LD_clearDisplay();
		dtostrf(Uzerolevel, 4, 0, zbuf);
		LD_printString_12x16("Uzero", 2, 0);
		LD_printString_12x16(zbuf, 70, 0);
		dtostrf(Izerolevel, 4, 0, zbuf);
		LD_printString_12x16("Izero", 2, 3);
		LD_printString_12x16(zbuf, 70, 3);
#ifdef USE_ENCODER
	} while (key.repeat());
#else
	} while (0);
#endif

	_Uzerolevel = (uint16_t)Uzerolevel;
	_Izerolevel = (uint16_t)Izerolevel;
}
*/

void check_ZeroCross()
{
	zcDetectedOK = (TEH.CounterZC > 50);
}

