
#ifdef USE_TASK_INFO
void Info_task(void * parameter)
{
	for (;;)
	{
		delay(100);
#else
void update_Info()
{
	{
#endif
		if ((millis() - msPrint) > showPeriod)
		{
			LD_DEBUG("ZC");
			check_ZeroCross();
			LD_DEBUG("SP");
			TEH.Pset = selectPower();
			LD_DEBUG("PS");
			print_Serial();
			LD_DEBUG("DS");
			update_DS();
//			DS[0].writeCorrection(12, 0, 0);
//			DS[0].writeCorrection(12, -16, 120);

#ifndef USE_TASK_INFO
			LD_DEBUG("LD");
			display_Oled();
//			log_info_addstr("PrevDisplay: ");
//			log_info_addstr(String(msDisplay));
#endif //!TASK_SHOW 
			LD_DEBUG("MB");
			update_Modbus();
			LD_DEBUG("WI");
			check_WiFi();
			LD_DEBUG("CS");
			check_Serial();
			D(INFOcore = xPortGetCoreID());
			LD_DEBUG("D1");
			print_More();
			LD_DEBUG("D2");
			print_Debug();
			LD_DEBUG("RC");
			reset_Counters();
			msPrint = millis();
			//log_info_addstr("PrevPrint: ");
			//log_info_addstr(String(msPrint));

		}
	}
}

void setPower(uint16_t Ptmp)
{
	Premote = Ptmp;
}

uint16_t selectPower() // Check here for LocalControl flag, Modbus heartbeat and priority of sources.
{
	uint16_t Plocal;
	if (RemoteON) Plocal = Premote;
	else Plocal = Pencoder;
	return Plocal;
}

/*
void setPower(uint16_t Ptmp)
{
#ifdef USE_MODBUS
	mb.Hreg(hrPSET, Ptmp);
#endif
	Premote = Ptmp;
}

uint16_t selectPower() // Check here for LocalControl flag, Modbus heartbeat and priority of sources.
{
	uint16_t Plocal;
#ifdef USE_MODBUS
	if (mbMasterOK) Premote = mb.Hreg(hrPSET);
#endif
	if (RemoteON) Plocal = Premote;
	else Plocal = Pencoder;
	return Plocal;
}
*/

void check_Encoder()
{
#ifdef USE_ENCODER
	key.readkey();
	if (showSetMenu) key.readencoder();     // можно не так часто

/*
	{
		if (key.encoder)       // вращение
		{
			Pencoder += int(ENCODER_STEP * key.encoder * abs(key.encoder));
			Pencoder = (Pencoder < 0) ? 0 : (Pencoder > POWER_MAX) ? POWER_MAX : Pencoder;
			setPower(Pencoder);	// мощность будет меняться во время кручения энкодера
			display_OledPower(Pencoder);
			key.encoder = 0;
		}
	}
*/

	if ((millis() - msKeys) > 200)
	{
		msKeys = millis();
		check_Keys();
		//if (showSetMenu) display_Oled();
	}
#endif
}


void check_Keys()
{
#ifdef USE_ENCODER
	if (key.shot_press())     // Короткое нажатие кнопки
	{
		LD_init();
		if (!RemoteON)
		{
			showSetMenu = !showSetMenu;
			if (showSetMenu) Pencoder = TEH.Pset;
			log_debug_ln(". ENCODER Short while Local");
		}
		else
		{
			showPower = !showPower;
			LD_clearDisplay();
			LD_printString_12x16("switch ...", 2, 6); // индикатор короткого нажатия на энкодер
			log_debug_ln(". ENCODER Short while Remote");
		}
	}
	// Долгое нажатие кнопки - переход с МБ на локальное управление !!
	if (key.long_press())
	{
		LD_clearDisplay();
		showSetMenu = false;
		showPower = true;
		setPower(0);
		Pencoder = 0;
		RemoteON = !RemoteON;
		log_info_ln(". ENCODER Long Press");
	}

	/*
		if (key.encoder)       // вращение
		{
			Pencoder += int(ENCODER_STEP * key.encoder * abs(key.encoder));
			Pencoder = (Pencoder < 0) ? 0 : (Pencoder > POWER_MAX) ? POWER_MAX : Pencoder;
			setPower(Pencoder);	// мощность будет меняться во время кручения энкодера
			display_OledPower(Pencoder);
			key.encoder = 0;
		}
	*/

	if (key.encoder != 0)                   // вращение
	{
		if (showSetMenu) {
			Pencoder += int(ENCODER_STEP * key.encoder * abs(key.encoder));
			Pencoder = (Pencoder < 0) ? 0 : (Pencoder > POWER_MAX) ? POWER_MAX : Pencoder;
			//Pset = Pencoder;
			//setPower(Pset);	// мощность будет меняться во время кручения энкодера
			setPower(Pencoder);	// мощность будет меняться во время кручения энкодера
			display_OledPower(Pencoder);
		}
		key.encoder = 0;
	}

	if (key.previous_millis_down + 10000 < millis()) showSetMenu = false;
#endif
}

void check_Serial()
{
#ifdef USE_SETSERIAL
	String T1, Var;

	while (Serial.available()) //Serial port, пока не конец сообщения, читаем данные и формируем строку
	{
		char ch = Serial.read();
		Var += ch;
		if (ch == '\n')
		{
			Var.toUpperCase();        // ??
			if (Var.substring(0, 2) == "SP")
			{
				T1 = Var.substring(Var.indexOf("SP", 2) + 3); //команда
				Pserial = T1.toFloat();          //Выставленная мощность с Serial
				setPower(Pserial);
			}
			else if (Var.substring(0, 3) == "RST")
			{
				ESP.restart();
			}
			else if (Var.substring(0, 4) == "MORE")
			{
				showMore = true;
			}
			else if (Var.substring(0, 5) == "DEBUG")
			{
				showDebug = true;
			}
			Var = "";
		}
	}
#endif
}

void check_ZeroCross()
{
	zcDetectedOK = (TEH_CounterZC > 50);
}

void reset_Counters()
{
	TEH.CounterRMS = 0;
	TEH_CounterZC = 0;
	TEH_CounterTR = 0;

#ifndef USE_3PHASE
	TEH.CounterZC = 0;
	TEH.CounterTR = 0;
	TEH.CounterTRopen = 0;
	TEH.CounterTRclose = 0;
#endif
	/*
		_cntrZC = 0;
	#ifdef DEV_DEBUG
		cntrRMS = 0;
		_cntrTR = 0;
		_cntrTRopen = 0;
		_cntrTRclose = 0;
		_tmrTriacNow = 0;
		tmrOpen = 0;
		tmrClose = 0;
		adcUmax = 0;
		adcImax = 0;
	#endif
	*/
}
