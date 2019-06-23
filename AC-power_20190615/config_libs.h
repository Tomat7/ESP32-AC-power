#pragma once

#include "ACpower.h"
ACpower TEH(POWER_MAX, PIN_ZCROSS, PIN_TRIAC, PIN_U, PIN_I);

#ifdef ARDUINO_ARCH_ESP32

#include <WiFi.h>
//#include <ModbusIP_ESP8266.h>
IPAddress local_IP(ETHERNET_IP);
IPAddress gateway(IP_NETWORK + 254);
IPAddress subnet(255, 255, 255, 0);
#define MAC1 0x32           // бесполезно :-)
#define MAC2 0x00

#ifdef USE_OTA
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#endif //USE_OTA

#ifdef USE_WEBSERVER
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
WebServer server(80);
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
ASOLED LD(SH1106, 400000);
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
