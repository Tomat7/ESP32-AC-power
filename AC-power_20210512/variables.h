#pragma once

TaskHandle_t taskInfo = NULL;

uint16_t Pweb = 0, Pmodbus = 0, Pserial = 0, Premote = 9;
int16_t Pencoder = 0;
uint32_t msPrint, msKeys, msDisplay;
uint8_t cntrDSerrors = 0;
uint16_t wifiErrors = 0;

bool wifiConnectOK = false;
bool showSetMenu = false;
bool showPower = true;
bool RemoteON = true;
bool mbMasterOK = true;
bool zcDetectedOK = false;
bool rmsCalibrated = false;
volatile uint32_t INFOcore = 6, OLEDcore = 8;

uint8_t showInfo = 0;
uint16_t showPeriod = SHOW_PERIOD;
bool showMore = false;
bool showDebug = false;

String strVersion, strVer, strConfig; // , strInfo;

#ifdef U_CORRECTION
static float Ucorr[25] = U_CORRECTION;
#endif
