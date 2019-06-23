
#ifdef TASK_INFO
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
		if ((millis() - msPrint) > SHOW_PERIOD)
		{
			check_ZeroCross();
			TEH.Pset = selectPower();
			print_Serial();
			update_DS();
#ifndef TASK_INFO
			display_Oled();
#endif //!TASK_SHOW 
			update_Modbus();
			check_WiFi();
			check_Serial();
			D(INFOcore = xPortGetCoreID());
			print_Debug1();
			print_Debug2();
			reset_Counters();
			msPrint = millis();
			DPRINTF("PrevPrint: ", msPrint);
			DPRINTF("PrevDisplay: ", msDisplay);
		}
	}
}


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

void check_Encoder()
{
#ifdef USE_ENCODER
	key.readkey();
	if (showSetMenu) key.readencoder();     // можно не так часто

	if ((millis() - msKeys) > 200)
	{
		msKeys = millis();
		check_Keys();
		if (showSetMenu) display_Oled();
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
			DPRINTLN(". ENCODER Short while Local");
		}
		else
		{
			showPower = !showPower;
			LD_clearDisplay();
			LD_printString_12x16("switch ...", 2, 6); // индикатор короткого нажатия на энкодер
			DPRINTLN(". ENCODER Short while Remote");
		}
	}
	// Долгое нажатие кнопки - переход с МБ на локальное управление !!
	if (key.long_press())
	{
		showSetMenu = false;
		showPower = true;
		setPower(0);
		Pencoder = 0;
		RemoteON = !RemoteON;
		PRINTLN(". ENCODER Long Press");
	}

	if (key.encoder)                   // вращение
	{
		if (showSetMenu) {
			Pencoder += int(ENCODER_STEP * key.encoder * abs(key.encoder));
			Pencoder = (Pencoder < 0) ? 0 : (Pencoder > POWER_MAX) ? POWER_MAX : Pencoder;
			//Pset = Pencoder;
			//setPower(Pset);	// мощность будет меняться во время кручения энкодера
			setPower(Pencoder);	// мощность будет меняться во время кручения энкодера
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
			Var = "";
		}
	}
#endif
}

void reset_Counters()
{
	TEH.CounterZC = 0;
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
