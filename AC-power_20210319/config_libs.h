#pragma once

#ifdef USE_3PHASE
#include "ACpower3.h"
ACpower3 TEH(PINS_PHASE0, PINS_PHASE1, PINS_PHASE2);
//ACpower3 TEH(PINS_PHASE0, PINS_PHASE1, PINS_PHASE2, POWER_MAX, true, false);
#else
#include "ACpower.h"
ACpower TEH(POWER_MAX, PIN_ZCROSS, PIN_TRIAC, PIN_U, PIN_I);
#endif

#ifdef ARDUINO_ARCH_ESP32

#include <WiFi.h>
//#include <ModbusIP_ESP8266.h>
#ifndef USE_DHCP
IPAddress local_IP(ETHERNET_IP);
IPAddress gateway(IP_NETWORK + 254);
IPAddress subnet(255, 255, 255, 0);
#endif
#define MAC1 0x32           // бесполезно :-)
#define MAC2 0x00

#ifdef USE_OTA
//#include <ESPmDNS.h>
//#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#endif //USE_OTA

#ifdef USE_WEBSERVER
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
WebServer httpd(80);
#endif //USE_WEBSERVER

#ifdef USE_TELNET
WiFiServer telnetd(23);
WiFiClient rClients[MAX_SRV_CLIENTS]; 
#endif //USE_WEBSERVER


#else
#error "Wrong module defined. Use ESP32 only."
#endif //ARDUINO_ARCH_ESP32

#ifdef USE_MODBUS
#include <ModbusIP_ESP8266.h>
#include "Modbus.h"
ModbusIP mb;
#endif //USE_MODBUS

#ifdef USE_OLED
#include "ASOLED.h"
ASOLED LD(SH1106, 100000);
//ASOLED LD(SSD1306);
#endif //USE_OLED

#ifdef USE_ENCODER
#include <ReadDigKey.h>
ReadDigKey key;
#endif

#ifdef USE_DS18B20
#include "DStemp.h"
DSThermometer DS[] = PIN_DS;
const int nSensor = sizeof(DS) / sizeof(DSThermometer);
float dsTemp[nSensor];
#endif
