#pragma once

TaskHandle_t taskADC = NULL;
TaskHandle_t taskInfo = NULL;
hw_timer_t * timerADC = NULL;
hw_timer_t * timerTriac = NULL;
volatile SemaphoreHandle_t smphADC, smphZC;
volatile SemaphoreHandle_t smphTriac;
volatile SemaphoreHandle_t smphRMS; // , smI, smU;
portMUX_TYPE muxTriac = portMUX_INITIALIZER_UNLOCKED;
portMUX_TYPE muxADC = portMUX_INITIALIZER_UNLOCKED;

volatile bool getI = true;
volatile bool takeADC = false;
volatile bool trOpened = false;
volatile uint8_t _zero = 1;
volatile uint8_t _pin = PIN_I;
volatile int16_t Xnow;
volatile uint32_t X2;

volatile uint64_t _summ = 0;
volatile uint64_t _I2summ = 0;
volatile uint64_t _U2summ = 0;

volatile uint32_t _cntr = 1;
volatile uint32_t _Icntr = 1;
volatile uint32_t _Ucntr = 1;

volatile uint16_t _zerolevel = 0;
volatile uint16_t _Izerolevel = 0;
volatile uint16_t _Uzerolevel = 0;

volatile uint32_t _msZCmillis = 0;
volatile uint16_t _angle = 0; 
volatile uint32_t _cntrZC = 0;
volatile uint32_t _tmrTriacNow = 0;
volatile uint32_t usPrevADC = 0;

float Inow = 0, Unow = 0;
int16_t Angle;
uint16_t Pset = 0, Pnow = 0;
uint16_t Pweb = 0, Pmodbus = 0, Pserial = 0, Premote = 9;
int16_t Pencoder = 0;
uint32_t msPrint, msKeys, msDisplay;
uint16_t ADCperSet;
uint16_t usADCinterval;
uint32_t cntrRMS = 0;
uint8_t cntrDSerrors = 0;
uint16_t wifiErrors = 50;

bool wifiConnectOK = false;
bool showSetMenu = false;
bool showPower = true;
bool RemoteON = true;
bool mbMasterOK = true;
bool zcDetectedOK = false;
bool rmsCalibrated = false;

#ifdef DEV_DEBUG
volatile uint32_t X2save = 0;
volatile uint32_t _cntrTR = 0;
volatile uint32_t _cntrTRopen = 0;
volatile uint32_t _cntrTRclose = 0;
volatile int16_t adcUmax, adcImax;
volatile uint16_t ADCprio = 7, ZCprio = 5, TRIACprio = 8, RMSprio = 9;
volatile uint32_t ZCcore = 3, ADCcore = 4, RMScore = 5, INFOcore = 6, TRIACcore = 7, OLEDcore = 8;
volatile uint32_t usZCduration, usZCtoTRIAC, _usZCmicros, _usTRmicros, usTRopen, tmrOpen, tmrClose;
#endif

String strVersion;

#ifdef U_CORRECTION
static const float Ucorr[25] = U_CORRECTION;
#endif
