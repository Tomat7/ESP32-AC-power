#pragma once

TaskHandle_t taskInfo = NULL;

uint16_t Pweb = 0, Pmodbus = 0, Pserial = 0, Premote = 9;
int16_t Pencoder = 0;
uint32_t msPrint, msKeys, msDisplay;
uint8_t cntrDSerrors = 0;
uint16_t wifiErrors = 50;

bool wifiConnectOK = false;
bool showSetMenu = false;
bool showPower = true;
bool RemoteON = true;
bool mbMasterOK = true;
bool zcDetectedOK = false;
bool rmsCalibrated = false;
volatile uint32_t INFOcore = 6, OLEDcore = 8;

String strVersion;

#ifdef U_CORRECTION
static float Ucorr[25] = U_CORRECTION;
#endif
