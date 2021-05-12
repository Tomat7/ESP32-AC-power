

void print_Serial()
{
	if (showInfo > 0)
	{
		log_info_ln("==================");
		log_info_ln("Pset: ", TEH.Pset);
		log_info_ln("Pnow: ", TEH.Pnow);
		log_info_ln("Angle: ", TEH.Angle);
	}
	DPRINTLN(showInfo);
}

void print_More()		// MORE start
{
	if (showInfo > 1)
	{
		log_info_ln("===");
		log_info_ln("Pweb: ", Pweb);
		log_info_ln("Penc: ", Pencoder);
		log_info_ln("RMScounter/sec: ", TEH.CounterRMS); //rmsCalcCounter = 0;
		log_info_ln("Ucounter: ", TEH._Ucntr);
		log_info_ln("Icounter: ", TEH._Icntr);
		log_info_ln("X2: ", TEH.X2);
	}
}

void print_Debug()
{
	if (showInfo > 2)
	{
		log_info_ln("===");
#ifdef USE_3PHASE
		log_info_ln("TEH._cntr: ", TEH._cntr);
		for (int i = 0; i < 3; i++)
		{
			log_info_ln(String(i));
			log_info_ln("  ZCross/sec: ", TEH.CounterZC[i]);
			TEH.CounterZC[i] = 0;
			log_info_ln("  TriacInts/sec: ", TEH.CounterTR[i]);
			TEH.CounterTR[i] = 0;

			log_info("  I = ", TEH.I[i]);
			log_info("  U = ", TEH.U[i]);
			log_info_ln("  P = ", TEH.P[i]);
		}
#else
		log_debug_f("U = ", TEH.Unow);
		log_debug_f("I = ", TEH.Inow);
		log_debug_f("ZCross/sec: ", TEH.CounterZC); //_zcCounter = 0;
		log_debug_f("TriacInts/sec: ", TEH.CounterTR); //_trCounter = 0;
		//D(log_info_f("TriacOpens/sec: ", TEH.CounterTRopen);) //_trOpens = 0;
		//D(log_info_f("TriacClose/sec: ", TEH.CounterTRclose);) //_trOpens = 0;
		//D(log_info_f("TimerOpen: ", TEH.TimerTRopen);) //_tmrRead = 0;
		//D(log_info_f("TimerClose: ", TEH.TimerTRclose);) //_tmrRead = 0;
		log_info_ln("--");
#endif // USE_3PHASE

		// DEBUG2 start
		//log_debug_f("_Summ ", int(_summ));	// ?? wtf
		//log_debug_f("_U ", (sqrt((float)_summ / (float)_cntr) * U_RATIO));  // ?? wtf
		//D(log_info_f("Umax: ", adcUmax);)
		//D(log_info_f("Imax: ", adcImax);)
		//D(log_info_ln("--");)
		D(log_info_ln("INFO core ", INFOcore));
		D(log_info_ln("OLED core ", OLEDcore));
		D(log_info_ln("RMS core ", TEH.RMScore));
		D(log_info_ln("RMS prio ", TEH.RMSprio));
		D(log_info_ln("ZCROSS core ", TEH.ZCcore));
		D(log_info_ln("ZCROSS prio ", TEH.ZCprio));
		D(log_info_ln("TRIAC core ", TEH.TRIACcore));
		D(log_info_ln("TRIAC prio ", TEH.TRIACprio));
		D(log_info_ln("ADC core ", TEH.ADCcore));
		D(log_info_ln("ADC prio ", TEH.ADCprio));
		D(log_info_ln("PRINT core ", xPortGetCoreID()));
		D(log_info_ln("PRINT prio ", uxTaskPriorityGet(NULL)));

		D(log_info_ln("--"));

		//D(log_info_f("ZCdn duration ", usZCduration);)
		//D(log_info_f("ZCtoTRIAC ", usZCtoTRIAC);)
		//D(log_info_f("TRIAC open uSec ", usTRopen);)
		//D(log_info_f("portTICK_PERIOD ", portTICK_PERIOD_MS);)
		//log_debug_f("local_buf ", Pencoder);
		// DEBUG end
		//log_info_ln(strInfo);
		//strInfo = "";
		log_info_ln("DisplayPeriod(ms): ", (millis() - msPrint));
	}
}
