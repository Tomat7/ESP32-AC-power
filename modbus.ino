void setup_Modbus()
{
#ifdef USE_MODBUS
    mb.slave();
    mb.addHreg(hrSECONDS);
    mb.addHreg(hrDSTEMP);
    mb.addHreg(hrPSET);
    mb.addHreg(hrPNOW);
    mb.addHreg(hrUNOW);
    mb.addHreg(hrINOW);
    mb.addHreg(hrU_CNTR);
    mb.addHreg(hrI_CNTR);
    PRINTLN("+ MODBUS Slave started.");
#else
    PRINTLN("-- NO MODBUS in this version.");
#endif
}

void update_Modbus()
{
#ifdef USE_MODBUS
	// если мастер онлайн - он должен записывать 0 в регистр SECONDS
	// это будет признаком "живости" Мастера Modbus'а для модуля
	// и наоборот: не 0 в SECONDS - признак "живости" модуля для Мастера
	// хотя Мастеру логичнее отслеживать "живость" по GetQuality
	bool prevMasterOK = mbMasterOK;
	if ((mb.Hreg(hrSECONDS) == 0) && RemoteON) mb.Hreg(hrSECONDS, msPrint / 1000);

	mbMasterOK = (((uint16_t)(msPrint / 1000) - mb.Hreg(hrSECONDS)) < MB_TIMEOUT);
	
	if (!mbMasterOK) { PRINTF("-- MODBUS Master OFFline ", mb.Hreg(hrSECONDS));	}
	else { PRINTLN("+ MODBUS ok"); }
		
	if (mbMasterOK != prevMasterOK) setPower(0);
	else mb.Hreg(hrPSET, Pset);

	mb.Hreg(hrDSTEMP, round(dsTemp[0] * 100));
	//mb.Hreg(hrDSTEMP, _angle);
    mb.Hreg(hrPNOW, Pnow);
    mb.Hreg(hrUNOW, round(Unow));
    mb.Hreg(hrINOW, round(Inow * 1000));
      
	mb.Hreg(hrU_CNTR, _Ucntr);
	mb.Hreg(hrI_CNTR, _Icntr);
	//Pmodbus = mb.Hreg(hrPSET);
#endif
}

