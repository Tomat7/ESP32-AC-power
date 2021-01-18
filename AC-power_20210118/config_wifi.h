#pragma once

#define WIFI_NAME "Tomat1"
#define WIFI_PASS "filimon7"

#define OTA_PASS "filimon7"
#define OTA_PORT 8266

#if PLC_ID == 0x07
//#define USE_DHCP
#define OTA_HOSTNAME "PLC-7 POWER_v" VERSION_CODE
#endif

#if PLC_ID == 0x08
#define USE_DHCP
#define OTA_HOSTNAME "PLC-8 POWER_v" VERSION_CODE
#define ESP_HOSTNAME "PLC-8_esp32"
#endif

#ifndef USE_DHCP
#define IP_NETWORK 192, 168, 1, 0
#define IP_ADDR_BASE IP_NETWORK + 30
#define ETHERNET_IP IP_ADDR_BASE + PLC_ID  // задаём IP адрес Ethernet модуля 
#endif