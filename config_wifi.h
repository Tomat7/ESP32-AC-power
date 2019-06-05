#pragma once

//#define USE_DHCP
#ifndef USE_DHCP
#define IP_NETWORK 192, 168, 1, 0
#define IP_ADDR_BASE IP_NETWORK + 30
#define ETHERNET_IP IP_ADDR_BASE + PLC_ID  // задаём IP адрес Ethernet модуля 
#endif

#define WIFI_NAME "MyWiFiName"
#define WIFI_PASS "MyWiFiPass"

#define OTA_HOSTNAME "PLC-12 POWER_v" VERSION_CODE
#define OTA_PASS "OTApass"
#define OTA_PORT 8266
