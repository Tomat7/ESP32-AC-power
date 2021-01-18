#pragma once

//#define USE_DHCP
#ifndef USE_DHCP
#define IP_NETWORK 192, 168, 1, 0
#define IP_ADDR_BASE IP_NETWORK + 30
#define ETHERNET_IP IP_ADDR_BASE + PLC_ID  // задаём IP адрес Ethernet модуля 
#endif

#define WIFI_NAME "wifi1234"
#define WIFI_PASS "wifi1234"

#define OTA_HOSTNAME "PLC-7 POWER_v" VERSION_CODE
#define OTA_PASS "otapass123"
#define OTA_PORT 8266
