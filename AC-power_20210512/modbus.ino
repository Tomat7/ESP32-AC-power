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
#ifdef USE_3PHASE
  mb.addHreg(hrPNOW0);
  mb.addHreg(hrPNOW1);
  mb.addHreg(hrPNOW2);
#endif
  log_cfg_ln("+ MODBUS Slave started.");
#else
  log_cfg_ln("-- NO MODBUS in this version.");
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

  Pmodbus = mb.Hreg(hrPSET);

  if (mbMasterOK)
  {
    setPower(Pmodbus);  // test !!
    if (showInfo > 0) log_info_ln("+ MODBUS ok");
  }
  else
  {
    //	mb.Hreg(hrPSET, 0);
    if (showInfo > 0) log_info_ln("-- MODBUS Master OFFline ", mb.Hreg(hrSECONDS));
  }

  if (mbMasterOK != prevMasterOK) setPower(0);

  mb.Hreg(hrPSET, TEH.Pset);

  mb.Hreg(hrDSTEMP, round(dsTemp[0] * 100));
  //mb.Hreg(hrDSTEMP, _angle);
  //mb.Hreg(hrPNOW, TEH.Pnow);
  mb.Hreg(hrPNOW, TEH.Pavg);
  mb.Hreg(hrUNOW, round(TEH_UNOW));
  mb.Hreg(hrINOW, round(TEH_INOW * 1000));

//  mb.Hreg(hrU_CNTR, TEH._Ucntr);
//  mb.Hreg(hrI_CNTR, TEH._Icntr);
  mb.Hreg(hrU_CNTR, DS[0].THreg);
  mb.Hreg(hrI_CNTR, DS[0].TLreg);
  //Pmodbus = mb.Hreg(hrPSET);

#ifdef USE_3PHASE
  mb.Hreg(hrPNOW0, TEH.P[0]);
  mb.Hreg(hrPNOW1, TEH.P[1]);
  mb.Hreg(hrPNOW2, TEH.P[2]);
#endif

#endif
}
