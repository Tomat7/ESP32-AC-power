#ifdef TASK_ADC
void GetADC_task(void * parameter)
{
	for (;;)
	//labelStartADC:
	//if ((micros() - usPrevADC) > 10)
	{
		//esp_task_wdt_reset();
		//if (xSemaphoreTakeFromISR(smphZC, 0) == pdTRUE) delay(1);
		//delayMicroseconds(5);
		//usPrevADC = micros();
		portENTER_CRITICAL(&muxADC);
#else
void IRAM_ATTR GetADC_int()
{
	portENTER_CRITICAL_ISR(&muxADC);
	{
#endif

		if (takeADC)
		{
			Xnow = adcEnd(_pin) - _zerolevel;
			X2 = Xnow * Xnow;
			if (X2 < ADC_NOISE) X2 = 0;
			_summ += X2;
			_cntr++;
			adcStart(_pin);
			D(if (getI) { if (Xnow > adcImax) adcImax = Xnow; }
			else { if (Xnow > adcUmax) adcUmax = Xnow; });
		}
		else if (_cntr == 0)
		{
			adcEnd(_pin);
			takeADC = true;
			adcStart(_pin);
		}
		D(ADCcore = xPortGetCoreID());
		D(ADCprio = uxTaskPriorityGet(NULL));

#ifdef TASK_ADC
		portEXIT_CRITICAL(&muxADC);
	} 
	//goto labelStartADC; // close cycle for(;;)
}
#else
	}
	portEXIT_CRITICAL_ISR(&muxADC);
}
#endif


void IRAM_ATTR ZeroCross_int()
{
#ifdef ZC_CRAZY
	if ((millis() - _msZCmillis) > 5)
#endif
	{
		//xSemaphoreGiveFromISR(smphZC, NULL);
		D(_usZCmicros = micros());
		//D(X2save = X2);

		timerStop(timerTriac);
		digitalWrite(PIN_TRIAC, LOW);
		trOpened = false;
		_msZCmillis = millis();
		_zero++;
		_cntrZC++;

		if (_zero >= ADC_WAVES)
		{
			portENTER_CRITICAL_ISR(&muxADC);
			takeADC = false;

			if (getI)
			{
				_pin = PIN_U;
				getI = false;
				_zerolevel = _Uzerolevel;
				_I2summ = _summ;
				_Icntr = _cntr;
			}
			else
			{
				_pin = PIN_I;
				getI = true;
				_zerolevel = _Izerolevel;
				_U2summ = _summ;
				_Ucntr = _cntr;
			}

			adcAttachPin(_pin);
			_summ = 0;
			_cntr = 0;
			_zero = 0;
			adcStart(_pin);
			portEXIT_CRITICAL_ISR(&muxADC);
			xSemaphoreGiveFromISR(smphRMS, NULL);
		}
		timerWrite(timerTriac, _angle);
		timerStart(timerTriac);
		D(ZCcore = xPortGetCoreID());
		D(ZCprio = uxTaskPriorityGet(NULL));
		D(usZCduration = micros() - _usZCmicros);
	}
}

void IRAM_ATTR OpenTriac_int()
{
	_tmrTriacNow = timerRead(timerTriac);
	if ((_tmrTriacNow > ANGLE_MIN) && (_tmrTriacNow < ANGLE_MAX))
	{
		digitalWrite(PIN_TRIAC, HIGH);
		trOpened = true;
		xSemaphoreGiveFromISR(smphTriac, NULL);

		D(usZCtoTRIAC = micros() - _usZCmicros);
		D(tmrOpen = _tmrTriacNow);
		D(_usTRmicros = micros());
		D(_cntrTRopen++);
	}
	else
	{
		digitalWrite(PIN_TRIAC, LOW);
		trOpened = false;

		D(tmrClose = _tmrTriacNow);
		D(usTRopen = micros() - _usTRmicros);
		D(_cntrTRclose++);
	}
	timerStop(timerTriac);
	D(_cntrTR++);
	D(TRIACcore = xPortGetCoreID());
	D(TRIACprio = uxTaskPriorityGet(NULL));
}

